#include "collapser.h"
#include <QElapsedTimer>
#include <QDebug>


Collapser::Collapser(const BackendDataDto& dto):
    m_sockets(dto.m_sockets),
    m_dimensionsWidth(dto.m_dimensionsWidth),
    m_dimensionsHeight(dto.m_dimensionsHeight),
    m_dimensionsWidthHeight(m_dimensionsWidth*m_dimensionsHeight),
    m_numberOfTiles(dto.m_numberOfTiles),
    m_precollapsedTilesConstructionInstructions(dto.m_precollapsedTilesConstructionInstructions),
    m_weightmapConstructionInstructions(dto.m_weightmapConstructionInstructions),
    m_availableWeightLists(dto.m_availableWeightLists),
    m_randomGenerator(QRandomGenerator::global())
                                                 {
    //All available tiles
    for (int i = 0; i < m_sockets.length(); i++) {
        Tile appendThis(m_sockets.at(i));
        m_allTiles.append(appendThis);
    }
    //Fill with Non-Defined Tiles
    for (int i = 0;i <  m_dimensionsWidth*m_dimensionsHeight; i++){
        m_tileMap.append(-1);
        m_disadvantageWeightMap.append(0);
    }
}

void Collapser::startCollapsing(){
    collapse();
}

void Collapser::collapse(){
    QElapsedTimer timer;
    timer.start();
    int randpos1 = m_randomGenerator->bounded( m_dimensionsWidth*m_dimensionsHeight);
    qDebug() << "pos chosen:" << randpos1;
    int randtile1 = m_randomGenerator->bounded(m_numberOfTiles);
    m_tileMap.replace(randpos1, randtile1);
    emit tileMapChanged(randpos1, randtile1);
    int collapsed = 1;

    //emit tileMapChanged(tileMap);
    enableSurroundingIndecesToBeChecked(randpos1);
    QVector<int> lastTilesPlacedPos;

    bool noSolution = false;

    // bool noSolutionFound = false;
    for (int jjj = 0;; jjj++) {

        if (!m_tileMap.contains(-1) /*|| jjj > 2000*/){

            break;
        }
        int nextTilePos = 0;

        if (noSolution) {
            // When no solution is found we go back two steps and try again.
            // This often ends in an endless loop. This will be improved
            m_tileMap.replace(lastTilesPlacedPos.takeLast(), -1);
            nextTilePos = lastTilesPlacedPos.last();
            m_tileMap.replace(lastTilesPlacedPos.takeLast(), -1);
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
            const QList<int> applyTheseDisadvantageWeights = m_availableWeightLists.at(m_disadvantageWeightMap
                                                                                                      .at(nextTilePos));
            int disadvantgeWeightOfThisTile = applyTheseDisadvantageWeights.at(randomTile);


            if (disadvantgeWeightOfThisTile > 1 ) {
                if ((m_randomGenerator->bounded(disadvantgeWeightOfThisTile) != 1)) { // Weight is applied. Continuing
                    continue; // prevents that tile will never be chosen
                }           // Even when only tile that fits
            }





            if (checkIfTileFits(nextTilePos, m_allTiles.at(randomTile))) {

               m_tileMap.replace(nextTilePos, randomTile);



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
int Collapser::calculateIndexToCollapseNext(){
    // Fill list with full max entropy
    QList<int> entropyMap;
    for (int i = 0; i <  m_dimensionsWidthHeight; i++) {
        entropyMap.append(m_numberOfTiles);
    }
    //  for(int i = 0; i < m_indecesToCheck.size();i++){
    //      entropyMap.append(m_numberOfTiles);
    //}

    // Iterate over NON-Collapsed Tiles
    for (int pos = 0; pos < m_tileMap.length(); pos++) {


        if(!m_indecesToCheck.contains(pos) )
            continue;

        // qDebug() << "Staring checking all Tiles. Pos: " << pos;
        if (m_tileMap.at(pos) != -1) { // Skip Loop if tile is Collapsed
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

        for (int i = 0; i < m_allTiles.length(); i++) {

            Tile tileAtPos = m_allTiles.at(i);
            if (checkTop) {
                // qDebug() << "Checking Top...";
                if (m_tileMap.at(pos - m_dimensionsWidth) != -1) {
                    if (!m_allTiles.value(m_tileMap.at(pos - m_dimensionsWidth))
                             .checkEdge(2, tileAtPos.getEdgeSockets(0))) {
                        entropyMap[pos]--;
                        continue;
                    }
                }

                if (checkTopLeft) {
                    if (m_tileMap.at(pos - m_dimensionsWidth - 1) != -1) {
                        if (m_allTiles.value(m_tileMap.at(pos - m_dimensionsWidth - 1))
                                .getCornerSocket(2) != tileAtPos.getCornerSocket(0)) {
                            entropyMap[pos]--;
                            continue;
                        }
                    }
                }

                if (checkTopRight) {
                    if (m_tileMap.at(pos - m_dimensionsWidth + 1) != -1) {
                        if (m_allTiles.value(m_tileMap.at(pos - m_dimensionsWidth + 1))
                                .getCornerSocket(3) != tileAtPos.getCornerSocket(1)) {
                            entropyMap[pos]--;
                            continue;
                        }
                    }
                }
            }

            if (checkBottom) {
                // qDebug() << "Checking Bottom...";
                if (m_tileMap.at(pos + m_dimensionsWidth) != -1) {
                    if (!m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth))
                             .checkEdge(0, tileAtPos.getEdgeSockets(2))) {
                        entropyMap[pos]--;
                        continue;
                    }
                }

                if (checkBottomLeft) {
                    if (m_tileMap.at(pos + m_dimensionsWidth - 1) != -1) {
                        if (m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth - 1))
                                .getCornerSocket(1) != tileAtPos.getCornerSocket(3)) {
                            entropyMap[pos]--;
                            continue;
                        }
                    }
                }

                if (checkBottomRight) {
                    if (m_tileMap.at(pos + m_dimensionsWidth + 1) != -1) {
                        if (m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth + 1))
                                .getCornerSocket(0) != tileAtPos.getCornerSocket(2)) {
                            entropyMap[pos]--;
                            continue;
                        }
                    }
                }
            }
            // Left
            if (pos % m_dimensionsWidth != 0 && pos != 0) {
                if (m_tileMap.at(pos - 1) != -1) {
                    if (!m_allTiles.value(m_tileMap.at(pos - 1))
                             .checkEdge(1, tileAtPos.getEdgeSockets(3))) {
                        entropyMap[pos]--;
                        continue;
                    }
                }
            }
            // Right
            if ((pos + 1) % m_dimensionsWidth != 0 &&
                pos + 1 <  m_dimensionsWidthHeight) {
                if (m_tileMap.at(pos + 1) != -1) {
                    if (!m_allTiles.value(m_tileMap.at(pos + 1))
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

bool Collapser::checkIfTileFits(const int& pos,const Tile& tile) const{
    if (pos -  m_dimensionsWidth >= 0) {
        // qDebug() << "Checking Above";
        if (m_tileMap.at(pos -  m_dimensionsWidth) != -1) { // Skip if NOT collapsed
            if (!m_allTiles.value(m_tileMap.at(pos -  m_dimensionsWidth))
                     .checkEdge(2, tile.getEdgeSockets(0))) {
                return false;
            }
        }
        // Above left

        if ((pos -  m_dimensionsWidth) %  m_dimensionsWidth != 0 && (pos -  m_dimensionsWidth) != 0) {
            if (m_tileMap.at(pos -  m_dimensionsWidth - 1) != -1) {
                if (m_allTiles.value(m_tileMap.at(pos -  m_dimensionsWidth - 1))
                        .getCornerSocket(2) != tile.getCornerSocket(0))
                    return false;
            }
        }
        // Above right

        if ((pos -  m_dimensionsWidth + 1) %  m_dimensionsWidth != 0 &&
            pos + 1 <   m_dimensionsWidthHeight /*-1*/) {
            if (m_tileMap.at(pos -  m_dimensionsWidth + 1) != -1) {
                if (m_allTiles.value(m_tileMap.at(pos -  m_dimensionsWidth + 1))
                        .getCornerSocket(3) != tile.getCornerSocket(1)) {
                    return false;
                }
            }
        }
    }
    // Right
    if ((pos + 1) %  m_dimensionsWidth != 0 && pos + 1 <  m_dimensionsWidthHeight) {
        if (m_tileMap.at(pos + 1) != -1) {
            if (!m_allTiles.value(m_tileMap.at(pos + 1))
                     .checkEdge(3, tile.getEdgeSockets(1))) {
                return false;
            }
        }
    }
    // Below
    if (pos +  m_dimensionsWidth <  m_dimensionsWidthHeight) {
        // qDebug() << "Checking Below";
        if (m_tileMap.at(pos + m_dimensionsWidth) != -1) {
            if (!m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth))
                     .checkEdge(0, tile.getEdgeSockets(2))) {
                return false;
            }
        }
        // Below left

        if (pos + m_dimensionsWidth % m_dimensionsWidth != 0 /*&& pos != 0*/) {
            if (m_tileMap.at(pos + m_dimensionsWidth - 1) != -1) {
                if (m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth - 1))
                        .getCornerSocket(1) != tile.getCornerSocket(3))
                    return false;
            }
        }
        // Below right
        if ((pos + m_dimensionsWidth + 1) % m_dimensionsWidth != 0 &&
            pos + m_dimensionsWidth + 1 <  m_dimensionsWidthHeight) {
            if (m_tileMap.at(pos + m_dimensionsWidth + 1) != -1) {
                if (m_allTiles.value(m_tileMap.at(pos + m_dimensionsWidth + 1))
                        .getCornerSocket(0) != tile.getCornerSocket(2)) {
                    return false;
                }
            }
        }
    }

    // Left
    if (pos % m_dimensionsWidth != 0 && pos != 0) {
        if (m_tileMap.at(pos - 1) != -1) {
            if (!m_allTiles.value(m_tileMap.at(pos - 1))
                     .checkEdge(1, tile.getEdgeSockets(3)))
                return false;
        }
    }
    return true;

}

void Collapser::enableSurroundingIndecesToBeChecked(const int& pos){
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
        if(m_tileMap.at(pos-m_dimensionsWidth) == -1)
            m_indecesToCheck.insert(pos-m_dimensionsWidth);
    }
    //TopLeft
    if(checkTopLeft){
        if(m_tileMap.at(pos-m_dimensionsWidth-1) == -1)
            m_indecesToCheck.insert(pos-m_dimensionsWidth-1);
    }
    //TopRight
    if(checkTopRight){
        if(m_tileMap.at(pos-m_dimensionsWidth+1) == -1)
            m_indecesToCheck.insert(pos-m_dimensionsWidth+1);
    }
    //Bottom
    if(checkBottom){
        if(m_tileMap.at(pos+m_dimensionsWidth) == -1)
            m_indecesToCheck.insert(pos+m_dimensionsWidth);
    }
    //BottomLeft
    if(checkBottomLeft){
        if(m_tileMap.at(pos+m_dimensionsWidth-1) == -1)
            m_indecesToCheck.insert(pos+m_dimensionsWidth-1);
    }
    //BottomRight
    if(checkBottomRight){
        if(m_tileMap.at(pos+m_dimensionsWidth+1) == -1)
            m_indecesToCheck.insert(pos+m_dimensionsWidth+1);
    }
    //Left
    if(pos % m_dimensionsWidth != 0 && pos != 0){
        if(m_tileMap.at(pos-1) == -1)
            m_indecesToCheck.insert(pos-1);
    }
    //Right
    if((pos + 1) % m_dimensionsWidth != 0 &&
        pos + 1 <  m_dimensionsWidthHeight){
        if(m_tileMap.at(pos+1) == -1)
            m_indecesToCheck.insert(pos+1);
    }    // qDebug() << "Indeces to check: " << m_indecesToCheck.values();
}


