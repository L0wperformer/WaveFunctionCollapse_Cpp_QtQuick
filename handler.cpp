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
  qDebug() << "pos chosen:" << randpos1;
  int randtile1 = QRandomGenerator::global()->bounded(m_numberOfTiles);
  tileMap->replace(randpos1, randtile1);
  emit drawTile(randpos1, randtile1);
  int collapsedCount = 0;
  // bool noSolutionFound = false;
  for (int jjj = 0;; jjj++) {
    // while (!noSolutionFound) {

    // STOP condition: All collapsed

    if (!tileMap->contains(-1) /*|| jjj > m_dimensions * m_dimensions * 100*/)
      break;

    int nextTilePos = calculateIndexToCollapseNext();
    if (jjj % 1000 == 0)
      qDebug() << "Loop no. " << jjj << "Collapsed: " << collapsedCount;
    QList<int> tilesAlreadytried;
    while (1) {
      int randomTile = QRandomGenerator::global()->bounded(m_numberOfTiles);

      if (checkIfTileFits(nextTilePos, allTiles.at(randomTile))) {
        // qDebug() << "Placing new tile at pos: " << nextTilePos;
        tileMap->replace(nextTilePos, randomTile);
        emit drawTile(nextTilePos, randomTile);
        collapsedCount++;
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
  // qDebug() << "Checking pos: " << pos;

  // Tile tileToCheck = allTiles.at(tileMap->at(pos));
  //  Above
  if (pos - m_dimensions >= 0) {
    // qDebug() << "Checking Above";
    if (tileMap->at(pos - m_dimensions) != -1) { // Skip if NOT collapsed
      if (!allTiles.value(tileMap->at(pos - m_dimensions))
               .checkEdge(2, tile.getEdgeSockets(0))) {
        return false;
      }
    }
    // Above left

    if ((pos - m_dimensions) % m_dimensions != 0 && (pos - m_dimensions) != 0) {
      if (tileMap->at(pos - m_dimensions - 1) != -1) {
        if (allTiles.value(tileMap->at(pos - m_dimensions - 1))
                .getCornerSocket(2) != tile.getCornerSocket(0))
          return false;
      }
    }
    // Above right

    if ((pos - m_dimensions + 1) % m_dimensions != 0 &&
        pos + 1 < m_dimensions * m_dimensions /*-1*/) {
      if (tileMap->at(pos - m_dimensions + 1) != -1) {
        if (allTiles.value(tileMap->at(pos - m_dimensions + 1))
                .getCornerSocket(3) != tile.getCornerSocket(1)) {
          return false;
        }
      }
    }
  }
  // Right
  if ((pos + 1) % m_dimensions != 0 && pos + 1 < m_dimensions * m_dimensions) {
    if (tileMap->at(pos + 1) != -1) {
      if (!allTiles.value(tileMap->at(pos + 1))
               .checkEdge(3, tile.getEdgeSockets(1))) {
        return false;
      }
    }
  }
  // Below
  if (pos + m_dimensions < m_dimensions * m_dimensions) {
    // qDebug() << "Checking Below";
    if (tileMap->at(pos + m_dimensions) != -1) {
      if (!allTiles.value(tileMap->at(pos + m_dimensions))
               .checkEdge(0, tile.getEdgeSockets(2))) {
        return false;
      }
    }
    // Below left

    if (pos + m_dimensions % m_dimensions != 0 /*&& pos != 0*/) {
      if (tileMap->at(pos + m_dimensions - 1) != -1) {
        if (allTiles.value(tileMap->at(pos + m_dimensions - 1))
                .getCornerSocket(1) != tile.getCornerSocket(3))
          return false;
      }
    }
    // Below right
    if ((pos + m_dimensions + 1) % m_dimensions != 0 &&
        pos + m_dimensions + 1 < m_dimensions * m_dimensions) {
      if (tileMap->at(pos + m_dimensions + 1) != -1) {
        if (allTiles.value(tileMap->at(pos + m_dimensions + 1))
                .getCornerSocket(0) != tile.getCornerSocket(2)) {
          return false;
        }
      }
    }
  }

  // Left
  if (pos % m_dimensions != 0 && pos != 0) {
    if (tileMap->at(pos - 1) != -1) {
      if (!allTiles.value(tileMap->at(pos - 1))
               .checkEdge(1, tile.getEdgeSockets(3)))
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

  // Iterate over NON-Collapsed Tiles
  for (int pos = 0; pos < tileMap->length(); pos++) {
    // qDebug() << "Staring checking all Tiles. Pos: " << pos;
    if (tileMap->at(pos) != -1) { // Skip Loop if tile is Collapsed
      // Make entropy of collapsed tiles bigger than
      // Max entropy so it never gets chosen
      entropyMap[pos] = m_numberOfTiles + 1;
      continue;
    }

    // Skip if NOT collapsed

    bool checkTop = (pos - m_dimensions >= 0);

    bool checkTopLeft = ((pos - m_dimensions) % m_dimensions != 0) &&
                        ((pos - m_dimensions) > 0);
    bool checkTopRight = (pos - m_dimensions + 1) % m_dimensions != 0 &&
                         pos + 1 < m_dimensions * m_dimensions;

    bool checkBottom = pos + m_dimensions < m_dimensions * m_dimensions;

    bool checkBottomLeft = (pos + m_dimensions) % m_dimensions != 0;

    bool checkBottomRight =
        (pos + m_dimensions + 1) % m_dimensions != 0 &&
        pos + m_dimensions + 1 < m_dimensions * m_dimensions;

    for (int i = 0; i < allTiles.length(); i++) {

      Tile tileAtPos = allTiles.at(i);
      if (checkTop) {
        // qDebug() << "Checking Top...";
        if (tileMap->at(pos - m_dimensions) != -1) {
          if (!allTiles.value(tileMap->at(pos - m_dimensions))
                   .checkEdge(2, tileAtPos.getEdgeSockets(0))) {
            entropyMap[pos]--;
          }
        }

        if (checkTopLeft) {
          if (tileMap->at(pos - m_dimensions - 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensions - 1))
                    .getCornerSocket(2) != tileAtPos.getCornerSocket(0)) {
              entropyMap[pos]--;
            }
          }
        }

        if (checkTopRight) {
          if (tileMap->at(pos - m_dimensions + 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensions + 1))
                    .getCornerSocket(3) != tileAtPos.getCornerSocket(1)) {
              entropyMap[pos]--;
            }
          }
        }
      }

      if (checkBottom) {
        // qDebug() << "Checking Bottom...";
        if (tileMap->at(pos + m_dimensions) != -1) {
          if (!allTiles.value(tileMap->at(pos + m_dimensions))
                   .checkEdge(0, tileAtPos.getEdgeSockets(2))) {
            entropyMap[pos]--;
          }
        }

        if (checkBottomLeft) {
          if (tileMap->at(pos + m_dimensions - 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensions - 1))
                    .getCornerSocket(1) != tileAtPos.getCornerSocket(3)) {
              entropyMap[pos]--;
            }
          }
        }

        if (checkBottomRight) {
          if (tileMap->at(pos + m_dimensions + 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensions + 1))
                    .getCornerSocket(0) != tileAtPos.getCornerSocket(2)) {
              entropyMap[pos]--;
            }
          }
        }
      }
      // Left
      if (pos % m_dimensions != 0 && pos != 0) {
        if (tileMap->at(pos - 1) != -1) {
          if (!allTiles.value(tileMap->at(pos - 1))
                   .checkEdge(1, tileAtPos.getEdgeSockets(3))) {
            entropyMap[pos]--;
          }
        }
      }
      // Right
      if ((pos + 1) % m_dimensions != 0 &&
          pos + 1 < m_dimensions * m_dimensions) {
        if (tileMap->at(pos + 1) != -1) {
          if (!allTiles.value(tileMap->at(pos + 1))
                   .checkEdge(3, tileAtPos.getEdgeSockets(1))) {
            entropyMap[pos]--;
          }
        }
      }
    }
  }
  // Iterate over collapsed Tiles
  //===OLD POSSIBLY TRASH CODE???===
  //    for (int index = 0; index < tileMap->length(); index++) {

  //      if (tileMap->at(index) == -1)
  //        continue;
  //      // qDebug() << "TileMap: " << *tileMap;
  //      Tile tileAtPos = allTiles.at(tileMap->at(index));
  //      // Check Above
  //      if (index - m_dimensions >= 0) {
  //        // Directly above
  //        if (tileMap->at(index - m_dimensions) != -1) { // Skip if collapsed

  //          for (int i = 0; i < allTiles.length(); i++) {
  //            if (tileAtPos.checkEdge(0, allTiles.value(i).getEdgeSockets(2)))
  //              entropyMap[index - m_dimensions]--;
  //          }
  //        }
  //        // Above Left
  //        if (index-m_dimensions % m_dimensions != 0 && index-m_dimensions !=
  //        0
  //        /*&&
  //            index - m_dimensions - 1 >= 0*/) {
  //          if (tileMap->at(index - m_dimensions - 1) == -1) {
  //            for (int i = 0; i < allTiles.length(); i++) {
  //              if (tileAtPos.getCornerSocket(0))
  //                entropyMap[index - m_dimensions - 1]--;
  //            }
  //          }
  //        }

  //        // Above Right
  //        if ((index + 1) % m_dimensions != 0 &&
  //            index + 1 < m_dimensions * m_dimensions) {
  //          if (tileMap->at(index - m_dimensions + 1) == -1 &&
  //              (index + 1) % m_dimensions != 0) {
  //            for (int i = 0; i < allTiles.length(); i++) {
  //              if (tileAtPos.checkEdge(1,
  //              allTiles.value(i).getEdgeSockets(3)))
  //                entropyMap[index - m_dimensions + 1]--;
  //            }
  //          }
  //        }
  //      }
  //      // Check Right
  //      if ((index + 1) % m_dimensions != 0 &&
  //          index + 1 < m_dimensions * m_dimensions) {
  //        if (tileMap->at(index + 1) == -1 && (index + 1) % m_dimensions != 0)
  //        {
  //          for (int i = 0; i < allTiles.length(); i++) {
  //            if (tileAtPos.checkEdge(1, allTiles.value(i).getEdgeSockets(3)))
  //              entropyMap[index + 1]--;
  //          }
  //        }
  //      }
  //      // Check Bottom
  //      if (index + m_dimensions < m_dimensions * m_dimensions - 1) {
  //        if (tileMap->at(index + m_dimensions) == -1) {
  //          for (int i = 0; i < allTiles.length(); i++) {
  //            if (tileAtPos.checkEdge(2, allTiles.value(i).getEdgeSockets(0)))
  //              entropyMap[index + m_dimensions]--;
  //          }
  //        }
  //        // Bottom Left
  //        if (index % m_dimensions != 0 && index != 0) {
  //          if (tileMap->at(index + m_dimensions - 1) == -1) {
  //            for (int i = 0; i < allTiles.length(); i++) {
  //              if (tileAtPos.checkEdge(3,
  //              allTiles.value(i).getEdgeSockets(1)))
  //                entropyMap[index + m_dimensions - 1]--;
  //            }
  //          }
  //        }

  //        // Bottom Right
  //        if ((index + 1) % m_dimensions != 0 &&
  //            index + 1 < m_dimensions * m_dimensions &&
  //            index + m_dimensions + 1 < m_dimensions * m_dimensions) {
  //          if (tileMap->at(index + m_dimensions + 1) == -1 &&
  //              (index + 1) % m_dimensions != 0) {
  //            for (int i = 0; i < allTiles.length(); i++) {
  //              if (tileAtPos.checkEdge(1,
  //              allTiles.value(i).getEdgeSockets(3)))
  //                entropyMap[index + m_dimensions + 1]--;
  //            }
  //          }
  //        }
  //      }
  //      // Check Left
  //      if (index % m_dimensions != 0 && index != 0) {
  //        if (tileMap->at(index - 1) == -1) {
  //          for (int i = 0; i < allTiles.length(); i++) {
  //            if (tileAtPos.checkEdge(3, allTiles.value(i).getEdgeSockets(1)))
  //              entropyMap[index - 1]--;
  //          }
  //        }
  //      }
  //    }

  // qDebug() << "Entropymap: " << entropyMap;
  //  For now, The first index of least entropy is returned. This will be
  //  changed to be random in the future qDebug() << "Min Entropy Value: "
  //        << *std::min_element(entropyMap.begin(), entropyMap.end());
  return entropyMap.indexOf(
      *std::min_element(entropyMap.begin(), entropyMap.end()));
}
