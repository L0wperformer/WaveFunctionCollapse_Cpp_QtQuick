#include "handler.h"
#include <QDebug>
#include <QRandomGenerator>
Handler::Handler(QList<QList<int>> sockets, int dimensions) {

  m_dimensions = dimensions;
  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  qDebug() << "Tiles: " << allTiles.length();
}

void Handler::drawGrid() {

  emit gridInit();

  // Fill with Non-defined Tiles
  tileMap = new QVector<int>(m_dimensions * m_dimensions, -1);
}

void Handler::startCollapsing() {
  qDebug() << "Starting Collapse Algorithm";

  // Collapse first tile randomly
  int randpos1 =
      QRandomGenerator::global()->bounded(m_dimensions * m_dimensions);
  int randtile1 = QRandomGenerator::global()->bounded(25);
  tileMap->replace(randpos1, randtile1);
  emit drawTile(randpos1, randtile1);
}
