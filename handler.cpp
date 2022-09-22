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
  QRandomGenerator rand;
  tileMap[rand.bounded(m_dimensions * m_dimensions)];
  emit drawTile(11, 10);
  emit drawTile(12, 23);
}
