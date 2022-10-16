#include "handler.h"
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>
Handler::Handler(QList<QList<int>> sockets, int dimensions, int numberOfTiles,
                 QList<int> weights) {
  m_dimensions = dimensions;
  m_sockets = sockets;
  m_numberOfTiles = numberOfTiles;
  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  // Fill with Non-defined Tiles
    tileMap = new QList<int>();
    for (int i = 0;i < m_dimensions*m_dimensions; i++){
        tileMap->append(-1);
    }
  m_disadvantageWeights = weights;
  qDebug() << "weights " << m_disadvantageWeights;
}

void Handler::drawGrid() {
  emit tileMapChanged(nullptr);
}

void Handler::collapse(){
    int randpos1 =
        QRandomGenerator::global()->bounded(m_dimensions * m_dimensions);
    qDebug() << "pos chosen:" << randpos1;
    int randtile1 = QRandomGenerator::global()->bounded(m_numberOfTiles);
    tileMap->replace(randpos1, randtile1);
      int collapsed = 1;

 emit tileMapChanged(tileMap);
    enableSurroundingIndecesToBeChecked(randpos1);
    QVector<int> lastTilesPlacedPos;

    bool noSolution = false;

    // bool noSolutionFound = false;
    for (int jjj = 0;; jjj++) {

      if (!tileMap->contains(-1) /*|| jjj > 2000*/){

        break;
      }
      int nextTilePos = 0;

      if (noSolution) {
        // When no solution is found we go back two steps and try again.
        // This often ends in an endless loop. This will be improved
        tileMap->replace(lastTilesPlacedPos.takeLast(), -1);
        nextTilePos = lastTilesPlacedPos.last();
        tileMap->replace(lastTilesPlacedPos.takeLast(), -1);
        collapsed -= 2;
        noSolution = false;
      } else {
          //timer.start();
        nextTilePos = calculateIndexToCollapseNext();
        //qDebug() << "Elapsed:" << timer.elapsed();
      }
  qDebug() << /*"Time: " <<timer.elapsed() <<*/ "collapsed: "<< collapsed << "percentage:" <<  ((double)collapsed  / (double)(m_dimensions*m_dimensions)) * 100 ;

      if (jjj % 100 == 0)
        qDebug() << "In Loop no." << jjj;

      QList<int> tilesAlreadytried;
      while (1) {
        int randomTile = QRandomGenerator::global()->bounded(m_numberOfTiles);
        if (m_disadvantageWeights.at(randomTile) > 1) {
          if ((QRandomGenerator::global()->bounded(m_disadvantageWeights.at(
                   randomTile)) != 1)) { // Weight is applied. Continuing
            continue; // prevents that tile will never be chosen
          }           // Even when only tile that fits
        }

        if (checkIfTileFits(nextTilePos, allTiles.at(randomTile))) {

        tileMap->replace(nextTilePos, randomTile);


          //emit drawTile(nextTilePos, randomTile);
          emit tileMapChanged(tileMap);
          enableSurroundingIndecesToBeChecked(nextTilePos);
          collapsed ++;
          lastTilesPlacedPos.append(nextTilePos);
          QThread::msleep(16); // Give QML engine time to process events

          break;
        }
        if (!tilesAlreadytried.contains(randomTile)) {
          tilesAlreadytried.append(randomTile);
        }
        if (tilesAlreadytried.length() == m_numberOfTiles) { // No tile fits

          qDebug() << "===No Solution Found, going Back===";
          noSolution = true;

          break;
        }
      }
    }

}
void Handler::startCollapsing() {
  qDebug() << "Starting Collapse Algorithm";
  Handler *toThread = new Handler(m_sockets, m_dimensions,m_numberOfTiles,m_disadvantageWeights);
  QThread *worker = new QThread();
  toThread->moveToThread(worker);
  connect(worker, &QThread::finished, worker, &QThread::deleteLater);
  connect(worker,&QThread::started,toThread,&Handler::collapse);
  connect(toThread, &Handler::tileMapChanged,this,[=](QList<int> *newList){
     tileMap = newList;
     emit tileMapChanged(nullptr);
  });

  worker->start(QThread::IdlePriority);
}

void Handler::enableSurroundingIndecesToBeChecked(int pos){
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
//Top
    if (checkTop)
             m_indecesToCheck.insert(pos-m_dimensions);
//TopLeft
    if(checkTopLeft)
             m_indecesToCheck.insert(pos-m_dimensions-1);
//TopRight
    if(checkTopRight)
             m_indecesToCheck.insert(pos-m_dimensions+1);
//Bottom
    if(checkBottom)
             m_indecesToCheck.insert(pos+m_dimensions);
//BottomLeft
     if(checkBottomLeft)
                 m_indecesToCheck.insert(pos+m_dimensions-1);
//BottomRight
     if(checkBottomRight)
                 m_indecesToCheck.insert(pos+m_dimensions+1);
//Left
     if(pos % m_dimensions != 0 && pos != 0)

                  m_indecesToCheck.insert(pos-1);
//Right
     if((pos + 1) % m_dimensions != 0 &&
             pos + 1 < m_dimensions * m_dimensions)
                  m_indecesToCheck.insert(pos+1);
    // qDebug() << "Indeces to check: " << m_indecesToCheck.values();

}

bool Handler::checkIfTileFits(int pos, Tile tile) {
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
//  for(int i = 0; i < m_indecesToCheck.size();i++){
//      entropyMap.append(m_numberOfTiles);
//}

  // Iterate over NON-Collapsed Tiles
  for (int pos = 0; pos < tileMap->length(); pos++) {


    if(!m_indecesToCheck.contains(pos) )
        continue;

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
            continue;
          }
        }

        if (checkTopLeft) {
          if (tileMap->at(pos - m_dimensions - 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensions - 1))
                    .getCornerSocket(2) != tileAtPos.getCornerSocket(0)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }

        if (checkTopRight) {
          if (tileMap->at(pos - m_dimensions + 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensions + 1))
                    .getCornerSocket(3) != tileAtPos.getCornerSocket(1)) {
              entropyMap[pos]--;
              continue;
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
            continue;
          }
        }

        if (checkBottomLeft) {
          if (tileMap->at(pos + m_dimensions - 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensions - 1))
                    .getCornerSocket(1) != tileAtPos.getCornerSocket(3)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }

        if (checkBottomRight) {
          if (tileMap->at(pos + m_dimensions + 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensions + 1))
                    .getCornerSocket(0) != tileAtPos.getCornerSocket(2)) {
              entropyMap[pos]--;
              continue;
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
            continue;
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
            continue;
          }
        }
      }
    }
  }

  //  For now, The first index of least entropy is returned. This will be
  //  changed to be random in the future

  return entropyMap.indexOf(
      *std::min_element(entropyMap.begin(), entropyMap.end()));
}



