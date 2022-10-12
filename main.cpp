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
      {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1}, // 11
      {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0}, // 12
      {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0}, // 13
      {0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0}, // 14
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1}, // 15
      {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0}, // 16
      {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 17
      {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // 18
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, // 19
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 20
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 21
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 22
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 23
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 24
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 25

  };

  QList<int> disadvantageWeights = {
      1, //0
      2, //1
      2, //2
      4, //3
      4, //4        These weights were chosen "normalized"
      4, //5        So x pieces of similar type get
      4, //6        a disadvantage of x
      4, //7
      4, //8
      4, //9
      4, //10
      4, //11
      4, //12
      4, //13
      4, //14
      2, //15
      2, //16
      8, //17
      8, //18
      8, //19
      8, //20
      8, //21
      8, //22
      8, //23
      8, //24
      1 //25
  };
//  QList<int> disadvantageWeights = {
//      1, //0
//      2, //1
//      2, //2
//      4, //3
//      4, //4        These weights were chosen "normalized"
//      4, //5        So x pieces of similar type get
//      4, //6        a disadvantage of x
//      4, //7
//      4, //8
//      4, //9
//      4, //10
//      4, //11
//      4, //12
//      4, //13
//      4, //14
//      2, //15
//      2, //16
//     20, //17
//      20, //18
//      20, //19
//      20, //20
//      8, //21
//      8, //22
//      8, //23
//      8, //24
//      1 //25
//  };

  Handler h(sockets, 50, sockets.length(),disadvantageWeights);
  auto view = new QQuickView;
  view->rootContext()->setContextProperty("handler", &h);
  view->setSource(QUrl("qrc:/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();


  return app.exec();
}
