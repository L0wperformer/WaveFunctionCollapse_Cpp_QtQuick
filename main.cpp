#include "handler.h"
#include <QGuiApplication>
#include <QList>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  //    QQmlApplicationEngine engine;
  //    const QUrl url(QStringLiteral("qrc:/main.qml"));
  //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
  //                     &app, [url](QObject *obj, const QUrl &objUrl) {
  //        if (!obj && url == objUrl)
  //            QCoreApplication::exit(-1);
  //    }, Qt::QueuedConnection);
  //    engine.load(url);

  // RULES
  QList<QList<int>> sockets = {
      //            INDEX
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // 0
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 1
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // 2
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, // 3
      {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // 4
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, // 5
      {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // 6
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, // 7
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 8
      {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 9
      {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, // 10

  };

  Handler h(sockets, 10);
  auto view = new QQuickView;
  view->rootContext()->setContextProperty("handler", &h);
  view->setSource(QUrl("qrc:/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();

  return app.exec();
}
