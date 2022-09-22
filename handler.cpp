#include "handler.h"
#include <QDebug>

Handler::Handler(QList<QList<int>> sockets) {

  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  qDebug() << "Tiles: " << allTiles.length();
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
