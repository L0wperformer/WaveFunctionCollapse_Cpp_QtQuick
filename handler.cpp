#include "handler.h"
#include <QDebug>
#include <QRandomGenerator>
Handler::Handler(QList<QList<int>> sockets) {

  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  qDebug() << "Tiles: " << allTiles.length();
}

void Handler::drawGrid(int gridSize) {

  emit gridInit(gridSize);

  // Fill with Non-defined Tiles
  QVector<int> negativeOnes(gridSize, -1);
  tileMap = new QVector<QVector<int>>(gridSize, negativeOnes);
}

void Handler::startCollapsing() {
  qDebug() << "Starting Collapse Algorithm";

  // Collapse first tile randomly
  emit drawTile(11, 10);
  emit drawTile(12, 23);
}
