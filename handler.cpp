#include "handler.h"
#include "tile.h"
#include <QDebug>

Handler::Handler() {
  test();
  // drawGrid(5);
}

void Handler::test() {

  QList<char> teilEinsKante = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

  QList<char> teilZweiKante = {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};

  Tile teilEins(teilEinsKante);
  Tile teilZwei(teilZweiKante);

  qDebug() << teilEins.checkEdge(1, teilZwei.getEdge(3));
}

void Handler::drawGrid(char gridSize) {

  emit gridInit(gridSize);

  //-1 = empty
  QVector<char> negativeOnes(gridSize, -1);
  tileMap = new QVector<QVector<char>>(gridSize, negativeOnes);
  // tileMap.fill(negativeOnes.fill(-1));
  qDebug() << *tileMap;

  // emit drawTile(-1);
}
