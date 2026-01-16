#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controller.h"
#include "webrtcmanager.h"
#include "websocketclient.h"
#include "mediacontroller.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WebSocketClient wsClient;
    MediaController mediaControler;
    WebRTCManager webrtcManager(&wsClient,&mediaControler);
    Controller controller(&wsClient, &webrtcManager);


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wsClient", &wsClient);
    engine.rootContext()->setContextProperty("webrtcManager", &webrtcManager);
    engine.rootContext()->setContextProperty("controller", &controller);

    engine.rootContext()->setContextProperty("mediaController", &mediaControler);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WeStudy", "Main");


    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
