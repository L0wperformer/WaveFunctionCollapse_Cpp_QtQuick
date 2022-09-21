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
  QList<QList<int>> listOfRules = {
      //            INDEX
      {1, 2, 1}, // 0
      {1, 2, 1}, // 1
      {1, 2, 1}, // 2
      {1, 2, 1}, // 3
      {1, 2, 1}, // 4
      {1, 2, 1}, // 5
      {1, 2, 1}, // 6
      {1, 2, 1}, // 7
      {1, 2, 1}, // 8
      {1, 2, 1}, // 9
      {1, 2, 1}, // 10

  };

  Handler h(listOfRules);
  auto view = new QQuickView;
  view->rootContext()->setContextProperty("handler", &h);
  view->setSource(QUrl("qrc:/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();

  return app.exec();
}
