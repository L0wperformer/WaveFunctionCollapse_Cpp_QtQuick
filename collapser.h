#ifndef COLLAPSER_H
#define COLLAPSER_H

#include <QObject>
#include <QSet>
#include <QRandomGenerator>
#include "backenddatadto.h"
#include "tile.h"


class Collapser : public QObject
{
    Q_OBJECT
signals:
    void tileMapChanged(int index, int newTile);
public:
    Collapser() = delete;
    Collapser(const BackendDataDto& dto);
    ~Collapser();

    void setNewAvailableTiles(const QList<QList<int>>& sockets);
    void resetTileMap();
    void setNewWeightMap(const QList<MapConstructor::constructParameters>& constructionParameters);

    int getDimensionsWidth(){return m_dimensionsWidth;}
    int getDimensionsHeight(){return m_dimensionsHeight;}
    int getWindowSizeHorizontalInPixels(){return m_windowSizeHorizontalInPixels;};
    QList<int> getTilesToBeColouredDifferently(){return m_tilesToBeColouredDifferently;}
    QList<int> getTileMap() {return m_tileMap;}
public slots:
    void startCollapsing();

private:
    QList<QList<int>> m_sockets;
    QList<MapConstructor::constructParameters> m_precollapsedTilesConstructionInstructions;
    QList<MapConstructor::constructParameters> m_weightmapConstructionInstructions;
    QList<QList<int>> m_availableWeightLists;
    QList<int> m_tileMap;
    QList<Tile> m_allTiles;
    QList<int> m_disadvantageWeightMap;
    QList<int> m_tilesToBeColouredDifferently;

    QSet<int> m_indecesToCheck;

    int m_dimensionsWidth;
    int m_dimensionsHeight;
    int m_windowSizeHorizontalInPixels;
    int m_dimensionsWidthHeight;
    int m_numberOfTiles;
    QRandomGenerator *m_randomGenerator;

    int m_continueNLoops;
    int m_collapsed ;

private:
    void collapse();
    int calculateIndexToCollapseNext();
    bool checkIfTileFits(const int& pos,const Tile& tile) const;
    void enableSurroundingIndecesToBeChecked(const int& pos);


};

#endif // COLLAPSER_H
