#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller.h"
#include <QQmlContext>
#include <wiringPi.h>
#include <QThread>
int main(int argc, char *argv[])
{


        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);
        controller t;
        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));
       engine.rootContext()->setContextProperty("test",&t);

        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                        QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
     //   t.Open();

        engine.load(url);

        return app.exec();
}
