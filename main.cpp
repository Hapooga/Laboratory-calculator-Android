#include <QGuiApplication>
#include <QQmlApplicationEngine>

///////////////////////
#include <QQmlContext>
#include "qmladapter.h"
///////////////////////

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/LabCalculator/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);


    ///////////////////////////////////////////////////
    QMLAdapter adapter;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("adapter", &adapter);
    ///////////////////////////////////////////////////


    engine.load(url);
    return app.exec();
}
