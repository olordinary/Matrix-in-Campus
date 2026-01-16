#pragma once

#include <QObject>
#include <QVideoSink>
#include <QVideoFrame>
#include <QImage>
#include <QTimer>
#include "webrtcmanager.h"


class MediaController:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
    Q_PROPERTY(bool isCapturing READ isCapturing NOTIFY isCapturingChanged)
    Q_PROPERTY(QVideoSink* remoteSink READ remoteSink WRITE setRemoteSink NOTIFY remoteSinkChanged)


public:
    explicit MediaController(QObject *parent = nullptr);
    ~MediaController();

    QVideoSink* videoSink() const { return m_videoSink; }
    void setVideoSink(QVideoSink *sink);

    QVideoSink* remoteSink() const { return m_remoteSink; }
    void setRemoteSink(QVideoSink *sink);

    bool isCapturing() const { return m_isCapturing; }

    Q_INVOKABLE void startCapture();
    Q_INVOKABLE void stopCapture();
    Q_INVOKABLE void setTargetResolution(int width, int height);
    Q_INVOKABLE void setTargetFps(int fps);
    Q_INVOKABLE void setQuality(int quality);
    Q_INVOKABLE void videoRecived(const QByteArray &data);

signals:
    void videoSinkChanged();
    void isCapturingChanged();
    void remoteSinkChanged();
    void videoFrameReady(const QByteArray &data); // 发送编码后的帧数据
    void rawFrameReady(const QImage &image);// 发送原始图像
    void statsUpdated(int fps, int frameCount);
    void logMessage(const QString &message);

private slots:
    void onVideoFrameChanged(const QVideoFrame &frame);
    void updateStats();


private:

    QByteArray encodeVideo(const QImage &image);
    QImage decodeVideo(const QByteArray &data);
    QImage videoFrameToImage(const QVideoFrame &frame);

    QVideoSink *m_videoSink = nullptr;
    QVideoSink *m_remoteSink = nullptr;
    bool m_isCapturing = false;


    int m_targetWidth = 640;
    int m_targetHeight = 480;
    int m_targetFps = 30;
    int m_quality = 70;  // JPEG 质量 (1-100)


    qint64 m_lastFrameTime = 0;
    int m_frameInterval = 33;  // 毫秒 (1000/30fps)

    QTimer *m_statsTimer = nullptr;
    bool shouldProcessFrame();  // 帧率控制
    int m_frameCount = 0;       // 接收帧计数
    int m_processedFrames = 0;  // 处理帧计数

};
