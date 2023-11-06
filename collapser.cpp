#include "collapser.h"
#include "mapconstructor.h"
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
    m_randomGenerator(QRandomGenerator::global()),
    m_windowSizeHorizontalInPixels(dto.m_windowSizeHorizontalInPixels),
    m_collapsed(1)
{

    MapConstructor mapConstructor(m_weightmapConstructionInstructions,m_dimensionsWidth,m_dimensionsHeight);
    m_disadvantageWeightMap = mapConstructor.constructWeightmap();
    m_tilesToBeColouredDifferently = mapConstructor.getTilesAffectedByMap();

    this->setNewAvailableTiles(m_sockets);
    this->resetTileMap();


}

void Collapser::setNewAvailableTiles(const QList<QList<int>>& sockets){
    m_allTiles.clear();
    //All available tiles
    for (int i = 0; i < sockets.length(); i++) {
        Tile appendThis(sockets.at(i));
        m_allTiles.append(appendThis);
    }
}

void Collapser::resetTileMap(){
   for (int i=0; i<m_dimensionsWidth*m_dimensionsHeight; i++){
       emit tileMapChanged(i,-1);
   }
}

void Collapser::setNewWeightMap(const QList<MapConstructor::constructParameters>& constructionParameters){
    MapConstructor mapConstructor(constructionParameters,m_dimensionsWidth,m_dimensionsHeight);
    m_collapsed = 1;
    m_disadvantageWeightMap = mapConstructor.constructWeightmap();
    m_tilesToBeColouredDifferently = mapConstructor.getTilesAffectedByMap();
}

void Collapser::startCollapsing(){
    collapse();
}

void Collapser::collapse(){

        m_tileMap.clear();
        for (int i = 0;i <  m_dimensionsWidth*m_dimensionsHeight; i++)  //TODO --> double code, needs refactoring
            m_tileMap.append(-1);
    QElapsedTimer timer;
    timer.start();

    int randpos1 = m_randomGenerator->bounded( m_dimensionsWidth*m_dimensionsHeight);
    int randtile1 = m_randomGenerator->bounded(m_numberOfTiles);


    m_tileMap.replace(randpos1, randtile1);
    emit tileMapChanged(randpos1, randtile1);

    enableSurroundingIndecesToBeChecked(randpos1);
    QVector<int> lastTilesPlacedPos;

    bool noSolution = false;
    int progressWhenNoSolutionOccured = 0;
    int goBackStepsUponNoSolution = 1;

    for (int jjj = 0;; jjj++) {

        if (!m_tileMap.contains(-1))
            break;

        int nextTilePos = 0;

        if (noSolution) {
            // When no solution is found we go back two steps and try again.
            // This often ends in an endless loop. This will be improved
//            for(int i = 0; i < goBackStepsUponNoSolution; i++){
//            int takeIndex = lastTilesPlacedPos.takeLast();
//            m_tileMap.replace(takeIndex, -1);
//            emit tileMapChanged(takeIndex, -1);
//            }
//            int takeIndex = lastTilesPlacedPos.takeLast();
//            nextTilePos = takeIndex;
//            m_tileMap.replace(takeIndex, -1);
//            emit tileMapChanged(takeIndex, -1);
//            collapsed -= goBackStepsUponNoSolution +1;

            //Testwise new implementation. Removes the surrounding tiles of conflicting tile
            //And attempts collapse again. This can be expanded.To incresingly remove tiles
            int pos = lastTilesPlacedPos.takeLast();
            qDebug() << /*"Time: " <<timer.elapsed() <<*/ "collapsed: "<< m_collapsed << "percentage:" <<  ((double)m_collapsed  / (double)( m_dimensionsWidthHeight)) * 100 ;
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
            bool checkLeft = pos % m_dimensionsWidth != 0 && pos != 0;
            bool checkRight = (pos + 1) % m_dimensionsWidth != 0 &&
                              pos + 1 <  m_dimensionsWidthHeight;
            m_tileMap.replace(pos,-1);
            emit tileMapChanged(pos,-1);
            if(checkTop){
                //qDebug() << "Top";
                m_tileMap.replace(pos-m_dimensionsWidth,-1);
                emit tileMapChanged(pos-m_dimensionsWidth,-1);

            if(checkTopLeft){
                //qDebug() << "TopL";
                m_tileMap.replace(pos-m_dimensionsWidth-1,-1);
                emit tileMapChanged(pos-m_dimensionsWidth-1,-1);
            }
            if(checkTopRight){
                //qDebug() << "TopR";
                m_tileMap.replace(pos-m_dimensionsWidth+1,-1);
                emit tileMapChanged(pos-m_dimensionsWidth+1,-1);
            }
            }
            if(checkLeft){
                //qDebug() << "Left";
                m_tileMap.replace(pos-1,-1);
                emit tileMapChanged(pos-1,-1);
            }
            if(checkRight){
                //qDebug() << "Right";
                m_tileMap.replace(pos+1,-1);
                emit tileMapChanged(pos+1,-1);
            }
             if(checkBottom){
                    if(checkBottomLeft){
                        //qDebug() << "BottomL";
                        m_tileMap.replace(pos+m_dimensionsWidth-1,-1);
                        emit tileMapChanged(pos+m_dimensionsWidth-1,-1);
                    }
                    if(checkBottomRight){
                        //qDebug() << "BottomR";
                        m_tileMap.replace(pos+m_dimensionsWidth+1,-1);
                        emit tileMapChanged(pos+m_dimensionsWidth+1,-1);
                    }

                //qDebug() << "Bottom";
                m_tileMap.replace(pos+m_dimensionsWidth,-1);
                emit tileMapChanged(pos+m_dimensionsWidth,-1);
            }


            //nextTilePos = calculateIndexToCollapseNext();
            m_collapsed -= 9;
            noSolution = false;
        } //else {
            nextTilePos = calculateIndexToCollapseNext();
        //}

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

                enableSurroundingIndecesToBeChecked(nextTilePos);
                lastTilesPlacedPos.append(nextTilePos);

                m_collapsed ++;
                if(m_collapsed > progressWhenNoSolutionOccured + 80)
                    goBackStepsUponNoSolution = 1;//When progress is x steps ahead we assume the
                                                  //Algorithm is not stuck anymore
                break;
            }

            if (!tilesAlreadytried.contains(randomTile)) {
                tilesAlreadytried.append(randomTile);
            }

            if (tilesAlreadytried.length() == m_numberOfTiles) { // No tile fits
                //qDebug() << "===No Solution Found, going Back===";
                //When no solution occures and the algorithm gets stuck
                //(=collapsed doesnt go up) then increase amount of steps
                //You go back
//                if(collapsed <= progressWhenNoSolutionOccured + 2 )
//                    goBackStepsUponNoSolution++;
//                progressWhenNoSolutionOccured = collapsed;
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
    // Iterate over NON-Collapsed Tiles
    for (int pos = 0; pos < m_tileMap.length(); pos++) {

        if(!m_indecesToCheck.contains(pos) )
            continue;

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
    }
}

Collapser::~Collapser(){
    delete m_randomGenerator;
}


