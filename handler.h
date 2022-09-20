#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Handler : public QObject {
  Q_OBJECT
public:
  Handler();

public slots:
  void drawGrid(int gridSize);
signals:
  void gridInit(int dimensions);
  void drawTile(int tileIndex);

private:
  QVector<QVector<int>> *tileMap;

  void test();
};

#endif // HANDLER_H
