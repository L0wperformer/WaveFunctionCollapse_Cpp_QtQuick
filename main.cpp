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
            1,  // 0
            2,  // 1
            2,  // 2
            4,  // 3
            4,  // 4        These weights were chosen "normalized"
            4,  // 5        So x pieces of similar type get
            4,  // 6        a disadvantage of x
            4,  // 7        Tiles that stop a line are
            4,  // 8        10x times as unlikely
            4,  // 9
            4,  // 10
            4,  // 11
            4,  // 12
            4,  // 13
            4,  // 14
            2,  // 15
            2,  // 16
            80, // 17
            80, // 18
            80, // 19
            80, // 20
            80, // 21
            80, // 22
            80, // 23
            80, // 24
            1   // 25
        };
//    QList<int> disadvantageWeights = {
//        1, // 0
//        1, // 1
//        1, // 2
//        1, // 3
//        1, // 4        All equally likely
//        1, // 5
//        1, // 6
//        1, // 7
//        1, // 8
//        1, // 9
//        1, // 10
//        1, // 11
//        1, // 12
//        1, // 13
//        1, // 14
//        1, // 15
//        1, // 16
//        1, // 17
//        1, // 18
//        1, // 19
//        1, // 20
//        1, // 21
//        1, // 22
//        1, // 23
//        1, // 24
//        1  // 25
//    };
//    QList<int> disadvantageWeights = {
//        2,   // 0
//        1,   // 1
//        1,   // 2
//        10,  // 3
//        10,  // 4        These weights make connections
//        10,  // 5        between diagonal and horizontal
//        10,  // 6        unlikely
//        10,  // 7        resulting in long diagonals
//        10,  // 8        and clusters
//        10,  // 9
//        10,  // 10
//        100, // 11
//        100, // 12
//        100, // 13
//        100, // 14
//        5,   // 15
//        5,   // 16
//        80,  // 17
//        80,  // 18
//        80,  // 19
//        80,  // 20
//        80,  // 21
//        80,  // 22
//        80,  // 23
//        80,  // 24
//        20   // 25
//    };
//    QList<int> disadvantageWeights = {
//        1,  // 0
//        2,  // 1
//        2,  // 2
//        20, // 3
//        20, // 4        These weights were chosen to
//        20, // 5        encourage long diagonals
//        20, // 6        All pieces that end a diagonal
//        30, // 7        or arent diagonal
//        30, // 8        got a much higher weight
//        30, // 9
//        30, // 10
//        10, // 11
//        10, // 12
//        10, // 13
//        10, // 14
//        1,  // 15
//        1,  // 16
//        80, // 17
//        80, // 18
//        80, // 19
//        80, // 20
//        80, // 21
//        80, // 22
//        80, // 23
//        80, // 24
//        20   // 25
//    };

  //    QList<int> disadvantageWeights = {
  //        5, // 0
  //        2, // 1
  //        2, // 2
  //        5, // 3
  //        5, // 4        These weights were chosen "normalized"
  //        5, // 5        So x pieces of similar type get
  //        5, // 6        a disadvantage of x
  //        4, // 7
  //        4, // 8
  //        4, // 9
  //        4, // 10
  //        4, // 11
  //        4, // 12
  //        4, // 13
  //        4, // 14
  //        2, // 15
  //        2, // 16
  //        8, // 17
  //        8, // 18
  //        8, // 19
  //        8, // 20
  //        8, // 21
  //        8, // 22
  //        8, // 23
  //        8, // 24
  //        1  // 25
  //    };

  Handler h(sockets,50 ,27, sockets.length(), disadvantageWeights);
 auto view = new QQuickView;


  view->rootContext()->setContextProperty("handler", &h);
  view->setSource(QUrl("qrc:/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();

  return app.exec();
}
