#include "handler.h"
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>
Handler::Handler(const QList<QList<int>>& sockets, const int& dimensionsWidth,const int& dimensionsHeight,const int& numberOfTiles,const QList<QPair<int,int>>& precollapsed
                 ,const QList<int>& weights) {
  m_dimensionsWidth = dimensionsWidth;
  m_dimensionsHeight = dimensionsHeight;
  m_dimensionsWidthHeight = m_dimensionsWidth*m_dimensionsHeight;
  m_sockets = sockets;
  m_numberOfTiles = numberOfTiles;
  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  // Fill with Non-defined Tiles
    tileMap = new QList<int>();
    for (int i = 0;i <  m_dimensionsWidth*m_dimensionsHeight; i++){
        tileMap->append(-1);
    }

    for (const auto& item : precollapsed){
        m_precollapsedTiles.append(item);
        tileMap->replace(item.first,item.second);
    }

  m_disadvantageWeights = weights;
  qDebug() << "weights " << m_disadvantageWeights;
}

void Handler::drawGrid() {
  emit tileMapChanged(nullptr);
}

void Handler::collapse(){
    int randpos1 =
        QRandomGenerator::global()->bounded( m_dimensionsWidth*m_dimensionsHeight);
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
  qDebug() << /*"Time: " <<timer.elapsed() <<*/ "collapsed: "<< collapsed << "percentage:" <<  ((double)collapsed  / (double)( m_dimensionsWidthHeight)) * 100 ;

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
  Handler *toThread = new Handler(m_sockets, m_dimensionsWidth, m_dimensionsHeight, m_numberOfTiles,m_precollapsedTiles,m_disadvantageWeights);
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

void Handler::enableSurroundingIndecesToBeChecked(const int& pos){


    bool checkTop = (pos - m_dimensionsWidth >= 0);
    bool checkTopLeft = ((pos - m_dimensionsWidth) % m_dimensionsWidth != 0) &&
                        ((pos - m_dimensionsWidth) > 0);
    bool checkTopRight = (pos - m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
                         pos + 1 <  m_dimensionsWidthHeight;
    bool checkBottom = pos + m_dimensionsWidth <  m_dimensionsWidthHeight;
    bool checkBottomLeft = (pos + m_dimensionsWidth) % m_dimensionsWidth != 0;
    bool checkBottomRight =
        (pos + m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
        pos + m_dimensionsWidth + 1 <  m_dimensionsWidthHeight;
//Top
    if (checkTop)
             m_indecesToCheck.insert(pos-m_dimensionsWidth);

//TopLeft
    if(checkTopLeft)
             m_indecesToCheck.insert(pos-m_dimensionsWidth-1);
//TopRight
    if(checkTopRight)
             m_indecesToCheck.insert(pos-m_dimensionsWidth+1);
//Bottom
    if(checkBottom)
             m_indecesToCheck.insert(pos+m_dimensionsWidth);
//BottomLeft
     if(checkBottomLeft)
                 m_indecesToCheck.insert(pos+m_dimensionsWidth-1);
//BottomRight
     if(checkBottomRight)
                 m_indecesToCheck.insert(pos+m_dimensionsWidth+1);
//Left
     if(pos % m_dimensionsWidth != 0 && pos != 0)

                  m_indecesToCheck.insert(pos-1);
//Right
     if((pos + 1) % m_dimensionsWidth != 0 &&
             pos + 1 <  m_dimensionsWidthHeight)
                  m_indecesToCheck.insert(pos+1);
    // qDebug() << "Indeces to check: " << m_indecesToCheck.values();

}

bool Handler::checkIfTileFits(const int& pos, const Tile& tile) const {
  if (pos -  m_dimensionsWidth >= 0) {
    // qDebug() << "Checking Above";
    if (tileMap->at(pos -  m_dimensionsWidth) != -1) { // Skip if NOT collapsed
      if (!allTiles.value(tileMap->at(pos -  m_dimensionsWidth))
               .checkEdge(2, tile.getEdgeSockets(0))) {
        return false;
      }
    }
    // Above left

    if ((pos -  m_dimensionsWidth) %  m_dimensionsWidth != 0 && (pos -  m_dimensionsWidth) != 0) {
      if (tileMap->at(pos -  m_dimensionsWidth - 1) != -1) {
        if (allTiles.value(tileMap->at(pos -  m_dimensionsWidth - 1))
                .getCornerSocket(2) != tile.getCornerSocket(0))
          return false;
      }
    }
    // Above right

    if ((pos -  m_dimensionsWidth + 1) %  m_dimensionsWidth != 0 &&
        pos + 1 <   m_dimensionsWidthHeight /*-1*/) {
      if (tileMap->at(pos -  m_dimensionsWidth + 1) != -1) {
        if (allTiles.value(tileMap->at(pos -  m_dimensionsWidth + 1))
                .getCornerSocket(3) != tile.getCornerSocket(1)) {
          return false;
        }
      }
    }
  }
  // Right
  if ((pos + 1) %  m_dimensionsWidth != 0 && pos + 1 <  m_dimensionsWidthHeight) {
    if (tileMap->at(pos + 1) != -1) {
      if (!allTiles.value(tileMap->at(pos + 1))
               .checkEdge(3, tile.getEdgeSockets(1))) {
        return false;
      }
    }
  }
  // Below
  if (pos +  m_dimensionsWidth <  m_dimensionsWidthHeight) {
    // qDebug() << "Checking Below";
    if (tileMap->at(pos + m_dimensionsWidth) != -1) {
      if (!allTiles.value(tileMap->at(pos + m_dimensionsWidth))
               .checkEdge(0, tile.getEdgeSockets(2))) {
        return false;
      }
    }
    // Below left

    if (pos + m_dimensionsWidth % m_dimensionsWidth != 0 /*&& pos != 0*/) {
      if (tileMap->at(pos + m_dimensionsWidth - 1) != -1) {
        if (allTiles.value(tileMap->at(pos + m_dimensionsWidth - 1))
                .getCornerSocket(1) != tile.getCornerSocket(3))
          return false;
      }
    }
    // Below right
    if ((pos + m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
        pos + m_dimensionsWidth + 1 <  m_dimensionsWidthHeight) {
      if (tileMap->at(pos + m_dimensionsWidth + 1) != -1) {
        if (allTiles.value(tileMap->at(pos + m_dimensionsWidth + 1))
                .getCornerSocket(0) != tile.getCornerSocket(2)) {
          return false;
        }
      }
    }
  }

  // Left
  if (pos % m_dimensionsWidth != 0 && pos != 0) {
    if (tileMap->at(pos - 1) != -1) {
      if (!allTiles.value(tileMap->at(pos - 1))
               .checkEdge(1, tile.getEdgeSockets(3)))
        return false;
    }
  }
  return true;
}

int Handler::calculateIndexToCollapseNext() const {
  // Fill list with full max entropy
  QList<int> entropyMap;
  for (int i = 0; i <  m_dimensionsWidthHeight; i++) {
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

    bool checkTop = (pos - m_dimensionsWidth >= 0);
    bool checkTopLeft = ((pos - m_dimensionsWidth) % m_dimensionsWidth != 0) &&
                        ((pos - m_dimensionsWidth) > 0);
    bool checkTopRight = (pos - m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
                         pos + 1 <  m_dimensionsWidthHeight;
    bool checkBottom = pos + m_dimensionsWidth <  m_dimensionsWidthHeight;
    bool checkBottomLeft = (pos + m_dimensionsWidth) % m_dimensionsWidth != 0;
    bool checkBottomRight =
        (pos + m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
        pos + m_dimensionsWidth + 1 <  m_dimensionsWidthHeight;

    for (int i = 0; i < allTiles.length(); i++) {

      Tile tileAtPos = allTiles.at(i);
      if (checkTop) {
        // qDebug() << "Checking Top...";
        if (tileMap->at(pos - m_dimensionsWidth) != -1) {
          if (!allTiles.value(tileMap->at(pos - m_dimensionsWidth))
                   .checkEdge(2, tileAtPos.getEdgeSockets(0))) {
            entropyMap[pos]--;
            continue;
          }
        }

        if (checkTopLeft) {
          if (tileMap->at(pos - m_dimensionsWidth - 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensionsWidth - 1))
                    .getCornerSocket(2) != tileAtPos.getCornerSocket(0)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }

        if (checkTopRight) {
          if (tileMap->at(pos - m_dimensionsWidth + 1) != -1) {
            if (allTiles.value(tileMap->at(pos - m_dimensionsWidth + 1))
                    .getCornerSocket(3) != tileAtPos.getCornerSocket(1)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }
      }

      if (checkBottom) {
        // qDebug() << "Checking Bottom...";
        if (tileMap->at(pos + m_dimensionsWidth) != -1) {
          if (!allTiles.value(tileMap->at(pos + m_dimensionsWidth))
                   .checkEdge(0, tileAtPos.getEdgeSockets(2))) {
            entropyMap[pos]--;
            continue;
          }
        }

        if (checkBottomLeft) {
          if (tileMap->at(pos + m_dimensionsWidth - 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensionsWidth - 1))
                    .getCornerSocket(1) != tileAtPos.getCornerSocket(3)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }

        if (checkBottomRight) {
          if (tileMap->at(pos + m_dimensionsWidth + 1) != -1) {
            if (allTiles.value(tileMap->at(pos + m_dimensionsWidth + 1))
                    .getCornerSocket(0) != tileAtPos.getCornerSocket(2)) {
              entropyMap[pos]--;
              continue;
            }
          }
        }
      }
      // Left
      if (pos % m_dimensionsWidth != 0 && pos != 0) {
        if (tileMap->at(pos - 1) != -1) {
          if (!allTiles.value(tileMap->at(pos - 1))
                   .checkEdge(1, tileAtPos.getEdgeSockets(3))) {
            entropyMap[pos]--;
            continue;
          }
        }
      }
      // Right
      if ((pos + 1) % m_dimensionsWidth != 0 &&
          pos + 1 <  m_dimensionsWidthHeight) {
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



