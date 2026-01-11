#include "mediacontroller.h"
#include <QDebug>
#include <QBuffer>
#include <QByteArray>

MediaController::MediaController(QObject *parent)
    : QObject(parent)
{
}

void MediaController::onVideoFrame(const QVideoFrame &frame)
{
    QVideoFrame clonedFrame(frame);
    if (!clonedFrame.map(QVideoFrame::ReadOnly)) {
        return;
    }

    QImage image = clonedFrame.toImage();
    clonedFrame.unmap();

    if (image.isNull()) return;

    // 缩放到640x480
    QImage scaled = image.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 发送视频
    auto data = encodeVideo(scaled);
   emit videoFrameReady(data);
}

void MediaController::startAudio(QObject *audioInputObj)
{
    //
}

QByteArray MediaController::encodeVideo(const QImage &image) {
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPEG", 70);
    return data;

}
