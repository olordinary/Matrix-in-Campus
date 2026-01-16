//mediacontroll.cpp对从qml中得到视频帧进行编码、解码
#include "mediacontroller.h"
#include <QDebug>
#include <QBuffer>
#include <QDateTime>

MediaController::MediaController(QObject *parent)
    : QObject(parent)
{
    m_statsTimer = new QTimer(this);
    connect(m_statsTimer, &QTimer::timeout, this, &MediaController::updateStats);
    m_statsTimer->start(1000);

    m_frameInterval = 1000 / m_targetFps;

    qDebug() << "MediaController 初始化完成";
}

MediaController::~MediaController()
{
    stopCapture();
}

void MediaController::setVideoSink(QVideoSink *sink)
{
    if (m_videoSink == sink) return;

    if (m_videoSink) {
        disconnect(m_videoSink, &QVideoSink::videoFrameChanged, this, &MediaController::onVideoFrameChanged);
        qDebug() << "已断开之前的 VideoSink";
    }

    m_videoSink = sink;

    if (m_videoSink) {
        connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &MediaController::onVideoFrameChanged);
        qDebug() << "已连接新的 VideoSink";
    }

    emit videoSinkChanged();
}

void MediaController::setRemoteSink(QVideoSink *sink)
{
    m_remoteSink = sink;
}

void MediaController::videoRecived(const QByteArray &data)
{
    qDebug() << "开始处理romote ";
    if (data.isEmpty()) {
        qWarning() << "没有数据";
        return;
    }

    QImage image = decodeVideo(data);
    qDebug() << "解码结果:" << (image.isNull() ? "失败" : "成功");

    if (image.isNull()) {
        qWarning() << "解码失败";
    }
    qDebug() << "remoteSink :" << (m_remoteSink ? "ok" : "no");

    if (!m_remoteSink) {
        qWarning() << "remoteSink 未设置好";
        return;
    }
    QVideoFrame frame(image);

    m_remoteSink->setVideoFrame(frame);
    qDebug() << "视频帧已经成功";
}

void MediaController::startCapture()
{
    if (m_isCapturing) {
        return;
    }

    if (!m_videoSink) {
        qDebug() << "VideoSink 未设置";
        return;
    }

    m_isCapturing = true;
    m_lastFrameTime = 0;
    m_frameCount = 0;

    qDebug() << "开始捕获视频帧";
    emit isCapturingChanged();
}

void MediaController::stopCapture()
{
    if (!m_isCapturing) {
        return;
    }

    m_isCapturing = false;
    qDebug() << "停止捕获视频帧";
    emit isCapturingChanged();
}

void MediaController::setTargetResolution(int width, int height)
{
    m_targetWidth = width;
    m_targetHeight = height;

}

void MediaController::setTargetFps(int fps)
{
    m_targetFps = fps;
    m_frameInterval = 1000 / fps;
}

void MediaController::setQuality(int quality)
{
    m_quality = qBound(1, quality, 100);
}

bool MediaController::shouldProcessFrame()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    // 帧率控制
    if (currentTime - m_lastFrameTime < m_frameInterval) {
        return false;
    }

    m_lastFrameTime = currentTime;
    return true;
}

void MediaController::onVideoFrameChanged(const QVideoFrame &frame)
{
    m_frameCount++;
    if (!m_isCapturing) {
        return;
    }
    if (!frame.isValid()) {
        return;
    }
    // 帧率控制
    if (!shouldProcessFrame()) {
        return;
    }

    try {
        // 将QVideoFreame转换为 QImage
        QVideoFrame clonedFrame(frame);
        if (!clonedFrame.map(QVideoFrame::ReadOnly)) {
            qWarning() << "映射视频帧失败";
            return;
        }

        QImage image = clonedFrame.toImage();
        clonedFrame.unmap();

        if (image.isNull()) {
            qWarning() << "图像为空";
            return;
        }

        QImage scaled = image.scaled(m_targetWidth, m_targetHeight,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
        // 编码为 JPEG
        QByteArray encodedData = encodeVideo(scaled);
        if (encodedData.isEmpty()) {
            qWarning() << "编码失败";
            return;
        }

        m_processedFrames++;
        emit videoFrameReady(encodedData);

    } catch (const std::exception &e) {
        qWarning() << "处理帧失败:" << e.what();
    }
}

QByteArray MediaController::encodeVideo(const QImage &image)
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);

    bool success = image.save(&buffer, "JPEG", m_quality);

    if (!success) {
        qDebug() << "图像编码失败";
        return QByteArray();
    }

    return data;
}

QImage MediaController::decodeVideo(const QByteArray &data)
{
    QImage image;
    bool success = image.loadFromData(data, "JPEG");

    // 转换格式
    if (image.format() != QImage::Format_ARGB32) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    if (!success) {
        qWarning() << "解码失败";
    }

    return image;
}

void MediaController::updateStats()
{
    if (m_isCapturing && m_processedFrames > 0) {
       emit statsUpdated(m_processedFrames, m_frameCount);
    }

    m_processedFrames = 0;
    m_frameCount = 0;
}
