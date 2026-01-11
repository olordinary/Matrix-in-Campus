#pragma once

#include <QObject>
#include <QVideoFrame>
#include <QAudioSource>
#include <QIODevice>
// #include "webrtcManager.h"


class MediaController:public QObject
{
    Q_OBJECT

public:
   explicit MediaController(QObject* parent=nullptr);

public slots:
    // QML 调用
    void onVideoFrame(const QVideoFrame &frame);
    void startAudio(QObject *audioInputObj);


signals:
    // 通知WebRTCManager
    void videoFrameReady(const QByteArray &data);
    void audioFrameReady(const QByteArray &data);


private:
    QByteArray encodeVideo(const QImage &image);
    QAudioSource *m_audioSource = nullptr;
    QIODevice *m_audioDevice = nullptr;
};
