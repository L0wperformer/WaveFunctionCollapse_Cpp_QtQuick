#include "handler.h"
#include "tile.h"
#include <QDebug>

Handler::Handler() {
  test();
  // drawGrid(5);
}

void Handler::test() {

  QList<int> teilEinsKante = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

  QList<int> teilZweiKante = {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

  Tile teilEins(teilEinsKante);
  Tile teilZwei(teilZweiKante);

  qDebug() << teilEins.checkEdge(1, teilZwei.getEdge(3));
}

void Handler::drawGrid(int gridSize) {

  emit gridInit(gridSize);

  //-1 = empty
  QVector<int> negativeOnes(gridSize, -1);
  tileMap = new QVector<QVector<int>>(gridSize, negativeOnes);
  // tileMap.fill(negativeOnes.fill(-1));
  qDebug() << *tileMap;
  // TODO: drawTile muss über "koordinaten funktionieren"

  // emit drawTile(-1);
}
