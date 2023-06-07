#include "collapser.h"
#include <QElapsedTimer>
#include <QDebug>


Collapser::Collapser(const BackendDataDto& dto):
    m_sockets(dto.m_sockets),
    m_dimensionsWidth(dto.m_dimensionsWidth),
    m_dimensionsHeight(dto.m_dimensionsHeight),
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
