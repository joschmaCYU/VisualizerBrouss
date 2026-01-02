#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "brouss/src/compiler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Backend compiler;
    engine.rootContext()->setContextProperty("myBackend", &compiler);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("VisualizerBrouss", "Main");

    return app.exec();
}
