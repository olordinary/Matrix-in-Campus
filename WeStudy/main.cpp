#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controller.h"
#include "webrtcManager.h"
#include "websocketclient.h"
<<<<<<< HEAD
=======
#include "mediacontroller.h"
>>>>>>> bca9fd1 (without mediacapture)

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WebSocketClient wsClient;
    WebRTCManager webrtcManager(&wsClient);
    Controller controller(&wsClient, &webrtcManager);
<<<<<<< HEAD
=======
    MediaController mediaControler;
>>>>>>> bca9fd1 (without mediacapture)

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wsClient", &wsClient);
    engine.rootContext()->setContextProperty("webrtcManager", &webrtcManager);
    engine.rootContext()->setContextProperty("controller", &controller);
<<<<<<< HEAD

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl) {
                             QCoreApplication::exit(-1);
                         }
                     }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
=======
    engine.rootContext()->setContextProperty("mediaController", &mediaControler);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WeStudy", "Main");
>>>>>>> bca9fd1 (without mediacapture)

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
