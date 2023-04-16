#include "handler.h"
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>
Handler::Handler(const QList<QList<int>>& sockets, const int& dimensionsWidth,const int& dimensionsHeight,const int& numberOfTiles,const QList<constructParameters>& precollapedTilesConstructionInstructions
                 ,const QList<constructParameters>& weightmapConstructionInstructions, const QList<QList<int>>& availableWeightLists) {
  m_dimensionsWidth = dimensionsWidth;
  m_dimensionsHeight = dimensionsHeight;
  m_dimensionsWidthHeight = m_dimensionsWidth*m_dimensionsHeight;
  m_sockets = sockets;
  m_numberOfTiles = numberOfTiles;
  m_availableDisadvantageWeightList = availableWeightLists;
  m_weightmapConstructionInstructions = weightmapConstructionInstructions;
  m_precollapedTilesConstructionInstructions = precollapedTilesConstructionInstructions;
  m_randomGenerator = QRandomGenerator::global();
  m_fps = 60;


  for (int i = 0; i < sockets.length(); i++) {
    Tile appendThis(sockets.at(i));
    allTiles.append(appendThis);
  }
  // Fill with Non-defined Tiles
    tileMap = new QList<int>();
    for (int i = 0;i <  m_dimensionsWidth*m_dimensionsHeight; i++){
        tileMap->append(-1);
        m_disadvantageWeightMap.append(0);
    }


    for (const auto& item : weightmapConstructionInstructions) {//This is ugly
        int startIndex = -1;
        switch(item.indexType){
        case constructionStartIndexType::columnStartIndex:
            //column start cant be greater than width
            //Well.. Lets catch that
            startIndex = item.startIndex;
            break;
        case constructionStartIndexType::lineStartIndex:
            startIndex = m_dimensionsWidth * item.startIndex;
            break;
        case constructionStartIndexType::tileStartIndex:
            startIndex = item.startIndex;
            break;
        }

        int stepSize = -1;
        switch(item.direction){
        case constructionDirection::horizontal:
            stepSize = 1;
            break;
        case constructionDirection::vertical:
            stepSize = m_dimensionsWidth;
            break;
        }

        int endIndex = startIndex;
        if(item.applyLength != -1){
            endIndex = startIndex + item.applyLength * stepSize;
        }

        if(item.applyLength == -1 && item.jumpLinesColumns){
            endIndex = m_dimensionsWidthHeight -1;
        }

        if(item.applyLength == -1 && !item.jumpLinesColumns){
            switch(item.direction){ //Ew, Nesting
            case constructionDirection::horizontal:
                while((endIndex+1) % m_dimensionsWidth != 0)
                    endIndex++;
                break;

            case constructionDirection::vertical:
                while(true){
                    if(endIndex + m_dimensionsWidth > m_dimensionsWidthHeight -1 ) //Eeeeeeeeeewwwww, Nesting
                      break;
                    endIndex += m_dimensionsWidth;
                }
                break;
            }

        }

        int increaseIndex = -1;
        switch(item.direction){ //you again
        case constructionDirection::horizontal:
           increaseIndex = m_dimensionsWidth;
           break;
        case constructionDirection::vertical:
           increaseIndex = 1;
           break;
        }

        for(int i = 0; i < item.applyToHowManyConsecutiveLinesColumns; i++)
            for( int j = startIndex + increaseIndex*i ; j < endIndex+ increaseIndex*i; j += stepSize ){
                m_disadvantageWeightMap.replace(j,item.tileOrWeightMapIndex);
                }
   }
    m_performanceTimer	 = new QTimer(this);
    connect(m_performanceTimer, &QTimer::timeout,this, &Handler::updateCanvas);

//==============REPLACE THIS WITH NEW CONSTRUCTION PARAMETERS============
//    for (const auto& item : precollapsed){
//        m_precollapsedTiles.append(item);
//        tileMap->replace(item.first,item.second);
//    }

//    for  (auto item = weightMap.begin();item!= weightMap.end();++item){
//        QPair<int,int> range = item.key();
//        int weightMap = item.value();

//        if(range.second == -1)
//            range.second = m_dimensionsHeight*m_dimensionsWidth-1;

//        for(int i = range.first; i<= range.second;i++){
//            m_disadvantageWeightMap.replace(i,weightMap);
//        }

//    }
//    qDebug() << m_disadvantageWeightMap;

}

void Handler::drawGrid() {
  emit updateCanvas();
}

void Handler::collapse(){
    QElapsedTimer timer;
    timer.start();
    int randpos1 =
        m_randomGenerator->bounded( m_dimensionsWidth*m_dimensionsHeight);
    qDebug() << "pos chosen:" << randpos1;
    int randtile1 = m_randomGenerator->bounded(m_numberOfTiles);
    tileMap->replace(randpos1, randtile1);
    emit tileMapChanged(randpos1, randtile1);
      int collapsed = 1;

 //emit tileMapChanged(tileMap);
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
        int randomTile = m_randomGenerator->bounded(m_numberOfTiles);
        const QList<int> applyTheseDisadvantageWeights = m_availableDisadvantageWeightList.at(m_disadvantageWeightMap
                                                                                             .at(nextTilePos));
        if (applyTheseDisadvantageWeights.at(randomTile) > 1) {
          if ((m_randomGenerator->bounded(applyTheseDisadvantageWeights.at(randomTile)) != 1)) { // Weight is applied. Continuing
            continue; // prevents that tile will never be chosen
          }           // Even when only tile that fits
        }

        if (checkIfTileFits(nextTilePos, allTiles.at(randomTile))) {

        tileMap->replace(nextTilePos, randomTile);



        emit tileMapChanged(nextTilePos,randomTile);
             //
        //QThread::msleep(25);


          enableSurroundingIndecesToBeChecked(nextTilePos);
          collapsed ++;
          lastTilesPlacedPos.append(nextTilePos);

          //QThread::msleep(16); // Give QML engine time to process events

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
    qDebug() << "All Tiles Collapsed! Time: " << timer.elapsed();

}
void Handler::startCollapsing() {
  qDebug() << "Starting Collapse Algorithm";
  m_performanceTimer->start(1000/m_fps);
  Handler *toThread = new Handler(m_sockets, m_dimensionsWidth, m_dimensionsHeight, m_numberOfTiles,m_precollapedTilesConstructionInstructions,m_weightmapConstructionInstructions,m_availableDisadvantageWeightList);
  QThread *worker = new QThread();
  toThread->moveToThread(worker);
  connect(worker, &QThread::finished, worker, &QThread::deleteLater);
  connect(worker,&QThread::started,toThread,&Handler::collapse);
  connect(toThread, &Handler::tileMapChanged,this,[&](int index, int newTile){
     tileMap->replace(index, newTile);
  });

  worker->start();
}

void Handler::enableSurroundingIndecesToBeChecked(const int& pos){


    bool checkTop = (pos - m_dimensionsWidth >= 0);
    bool checkTopLeft = ((pos - m_dimensionsWidth) % m_dimensionsWidth != 0) &&
                        ((pos - m_dimensionsWidth) > 0);
    bool checkTopRight = checkTop && (pos - m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
                         pos + 1 <  m_dimensionsWidthHeight;
    bool checkBottom = pos + m_dimensionsWidth <  m_dimensionsWidthHeight;
    bool checkBottomLeft = checkBottom && ((pos + m_dimensionsWidth) % m_dimensionsWidth != 0);
    bool checkBottomRight =
        (pos + m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
        pos + m_dimensionsWidth + 1 <  m_dimensionsWidthHeight;
    m_indecesToCheck.remove(pos);
//Top
    if (checkTop){
        if(tileMap->at(pos-m_dimensionsWidth) == -1)
             m_indecesToCheck.insert(pos-m_dimensionsWidth);
    }
//TopLeft
    if(checkTopLeft){
        if(tileMap->at(pos-m_dimensionsWidth-1) == -1)
             m_indecesToCheck.insert(pos-m_dimensionsWidth-1);
    }
             //TopRight
    if(checkTopRight){
        if(tileMap->at(pos-m_dimensionsWidth+1) == -1)
             m_indecesToCheck.insert(pos-m_dimensionsWidth+1);
    }
//Bottom
    if(checkBottom){
        if(tileMap->at(pos+m_dimensionsWidth) == -1)
             m_indecesToCheck.insert(pos+m_dimensionsWidth);
    }
//BottomLeft
     if(checkBottomLeft){
         if(tileMap->at(pos+m_dimensionsWidth-1) == -1)
                 m_indecesToCheck.insert(pos+m_dimensionsWidth-1);
      }
//BottomRight
     if(checkBottomRight){
         if(tileMap->at(pos+m_dimensionsWidth+1) == -1)
                 m_indecesToCheck.insert(pos+m_dimensionsWidth+1);
     }
//Left
     if(pos % m_dimensionsWidth != 0 && pos != 0){
            if(tileMap->at(pos-1) == -1)
                  m_indecesToCheck.insert(pos-1);
     }
//Right
     if((pos + 1) % m_dimensionsWidth != 0 &&
             pos + 1 <  m_dimensionsWidthHeight){
         if(tileMap->at(pos+1) == -1)
                  m_indecesToCheck.insert(pos+1);
     }    // qDebug() << "Indeces to check: " << m_indecesToCheck.values();

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

  QList<int> chooseFromHere;
  int minValue = *std::min_element(entropyMap.begin(), entropyMap.end());
  int minValueIndex = entropyMap.indexOf(minValue);

  int i;
  while((i = entropyMap.indexOf(minValue,minValueIndex)) != -1){
          chooseFromHere.append(i);
          minValueIndex = i+1;
  }
  return chooseFromHere.at(m_randomGenerator->bounded(chooseFromHere.length()));

}

Handler::~Handler(){
    delete m_randomGenerator;
    delete tileMap;
}


