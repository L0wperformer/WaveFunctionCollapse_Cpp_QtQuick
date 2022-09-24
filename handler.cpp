#include "handler.h"
#include <QDebug>
#include <QRandomGenerator>
Handler::Handler(QList<QList<int>> sockets, int dimensions, int numberOfTiles) {

  m_dimensions = dimensions;
  m_numberOfTiles = numberOfTiles;

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
  int randtile1 = QRandomGenerator::global()->bounded(m_numberOfTiles);
  tileMap->replace(randpos1, randtile1);
  emit drawTile(randpos1, randtile1);

  // while (0) {
  int nextTile = calculateIndexToCollapseNext();
  qDebug() << nextTile;
  //}
}

int Handler::calculateIndexToCollapseNext() {
  // Fill list with full max entropy
  QList<int> entropyMap;
  for (int i = 0; i < m_dimensions * m_dimensions; i++) {
    entropyMap.append(m_numberOfTiles);
  }

  // Iterate over collapsed Tiles

  for (int index = 0; index < tileMap->length(); index++) {

    if (tileMap->at(index) == -1)
      continue;
    qDebug() << "TileMap: " << *tileMap;
    Tile tileAtPos = allTiles.at(tileMap->at(index));
    // Check Above
    if (index - m_dimensions > 0) {
      if (tileMap->at(index - m_dimensions) == -1) { // Skip if collapsed
        for (int i = 0; i < allTiles.length(); i++) {
          if (tileAtPos.checkEdge(0, allTiles.value(i).getEdge(2)))
            entropyMap[index - m_dimensions]--;
        }
      }
    }
    // Check Right
    if ((index + 1) % m_dimensions != 0 &&
        index + 1 < m_dimensions * m_dimensions - 1) {
      if (tileMap->at(index + 1) == -1 && (index + 1) % m_dimensions != 0) {
        for (int i = 0; i < allTiles.length(); i++) {
          if (tileAtPos.checkEdge(1, allTiles.value(i).getEdge(3)))
            entropyMap[index + 1]--;
        }
      }
    }
    // Check Bottom
    if (index + m_dimensions < m_dimensions * m_dimensions - 1) {
      if (tileMap->at(index + m_dimensions) == -1) {
        for (int i = 0; i < allTiles.length(); i++) {
          if (tileAtPos.checkEdge(2, allTiles.value(i).getEdge(0)))
            entropyMap[index + m_dimensions]--;
        }
      }
    }
    // Check Left
    if (index % m_dimensions != 0 && index != 0) {
      if (tileMap->at(index - 1) == -1) {
        for (int i = 0; i < allTiles.length(); i++) {
          if (tileAtPos.checkEdge(3, allTiles.value(i).getEdge(1)))
            entropyMap[index - 1]--;
        }
      }
    }
  }

  qDebug() << "Entropymap: " << entropyMap;
  return entropyMap.indexOf(*std::min(entropyMap.begin(), entropyMap.end()));
}
