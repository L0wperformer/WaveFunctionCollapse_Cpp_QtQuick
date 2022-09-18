#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "tile.h"

void test(){
    QList<char> teilEinsKante = {0,0,0,
                                 0,0,0,
                                 0,0,0,
                                 0,0,0};

    QList<char> teilZweiKante = {0,1,0,
                                 0,1,0,
                                 0,1,0,
                                 0,1,0};

  Tile teilEins(teilEinsKante);
  Tile teilZwei(teilZweiKante);

   qDebug() << teilEins.checkEdge(1,teilZwei.getEdge(2));

}



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    test();

    return app.exec();
}


