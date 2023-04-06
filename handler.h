#ifndef HANDLER_H
#define HANDLER_H
#include "definitions.h"
#include "tile.h"
#include <QList>
#include <QSet>
#include <QObject>
#include <QElapsedTimer>
#include <QVariant>
#include <QDebug>

class Handler : public QObject {
  Q_OBJECT
  Q_PROPERTY (QList<int> tileMap READ getTileMap NOTIFY tileMapChanged)
public:
  Handler(const QList<QList<int>>& sockets, const int& dimensionsWidth,const int& dimensionsHeight, const int& m_numberOfTiles,
        const QList<constructParameters>& precollapedTilesConstructionInstructions ,const QList<constructParameters>& weightmapConstructionInstructions, const QList<QList<int>>& availableWeightLists);


public slots:
  void drawGrid();
  void startCollapsing();


  int getDimensionsWidth() { return m_dimensionsWidth; }
  int getDimensionsHeight() {return m_dimensionsHeight; }
  QList<int> getTileMap() const{
      return (*tileMap);
  }


signals:
  void gridInit();
  void tileMapChanged(QList<int> *newMap);


private:
  QList<int> *tileMap;
  QVector<QObject*>  *objectTileMap;
  QList<QList<int>> m_rules;
  QList<Tile> allTiles;
  QList<int> m_disadvantageWeightMap;
  QList<QList<int>> m_availableDisadvantageWeightList;
  QList<constructParameters> m_weightmapConstructionInstructions;
  QList<constructParameters> m_precollapedTilesConstructionInstructions;
  QList<QList<int>> m_sockets;
  QSet<int> m_indecesToCheck;
  int m_dimensionsWidth;
  int m_dimensionsHeight;
  int m_dimensionsWidthHeight;
  int m_numberOfTiles;
  int calculateIndexToCollapseNext() const;
  bool checkIfTileFits(const int& pos,const Tile& tile) const;
  void enableSurroundingIndecesToBeChecked(const int& pos);
  void collapse();
};

#endif // HANDLER_H
