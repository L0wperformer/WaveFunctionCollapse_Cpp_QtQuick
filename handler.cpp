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
  int randpos1 = 0;
  // QRandomGenerator::global()->bounded(m_dimensions * m_dimensions);
  int randtile1 = QRandomGenerator::global()->bounded(m_numberOfTiles);
  tileMap->replace(randpos1, randtile1);
  emit drawTile(randpos1, randtile1);
  // bool noSolutionFound = false;
  for (int jjj = 0; jjj < 100; jjj++) {
    // while (!noSolutionFound) {
    int nextTilePos = calculateIndexToCollapseNext();
    qDebug() << nextTilePos;
    QList<int> tilesAlreadytried;
    while (1) {
      int randomTile = QRandomGenerator::global()->bounded(m_numberOfTiles);

      if (checkIfTileFits(nextTilePos, allTiles.at(randomTile))) {
        qDebug() << "Placing new tile at pos: " << nextTilePos;
        tileMap->replace(nextTilePos, randomTile);
        emit drawTile(nextTilePos, randomTile);
        break;
      }
      if (!tilesAlreadytried.contains(randomTile)) {
        tilesAlreadytried.append(randomTile);
      }
      if (tilesAlreadytried.length() == m_numberOfTiles) {
        break;
      }
    }
  }
}
bool Handler::checkIfTileFits(int pos, Tile tile) {

  // Tile tileToCheck = allTiles.at(tileMap->at(pos));
  //  Above
  if (pos - m_dimensions > 0) {
    if (tileMap->at(pos - m_dimensions) != -1) { // Skip if NOT collapsed
      if (!allTiles.value(tileMap->at(pos - m_dimensions))
               .checkEdge(2, tile.getEdge(0))) {
        return false;
      }
    }
  }
  // Right
  if ((pos + 1) % m_dimensions != 0 &&
      pos + 1 < m_dimensions * m_dimensions - 1) {
    if (tileMap->at(pos + 1) != -1) {
      if (!allTiles.value(tileMap->at(pos + 1)).checkEdge(3, tile.getEdge(1))) {
        return false;
      }
    }
  }
  // Below
  if (pos + m_dimensions < m_dimensions * m_dimensions - 1) {
    if (tileMap->at(pos + m_dimensions) != -1) {
      if (!allTiles.value(tileMap->at(pos + m_dimensions))
               .checkEdge(0, tile.getEdge(2))) {
        return false;
      }
    }
  }

  // Left
  if (pos % m_dimensions != 0 && pos != 0) {
    if (tileMap->at(pos - 1) != -1) {
      if (!allTiles.value(tileMap->at(pos - 1)).checkEdge(1, tile.getEdge(3)))
        return false;
    }
  }
  return true;
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
  // For now, The first index of least entropy is returned. This will be changed
  // to be random in the future
  // qDebug() << "Min Entropy Value: "
  //       << *std::min_element(entropyMap.begin(), entropyMap.end());
  return entropyMap.indexOf(
      *std::min_element(entropyMap.begin(), entropyMap.end()));
}
