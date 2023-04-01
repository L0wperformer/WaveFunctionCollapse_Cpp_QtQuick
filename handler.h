#ifndef HANDLER_H
#define HANDLER_H

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
  Handler(QList<QList<int>> sockets, int dimensionsWidth,int dimensionsHeight, int m_numberOfTiles,
        QList<QPair<int,int>> precollapsed ,QList<int> weights);


public slots:
  void drawGrid();
  void startCollapsing();


  int getDimensionsWidth() { return m_dimensionsWidth; }
  int getDimensionsHeight() {return m_dimensionsHeight; }
  QList<int> getTileMap(){
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
  QList<int> m_disadvantageWeights;
  QList<QList<int>> m_sockets;
  QList<QPair<int,int>> m_precollapsedTiles;
  QSet<int> m_indecesToCheck;
  int m_dimensionsWidth;
  int m_dimensionsHeight;
  int m_dimensionsWidthHeight;
  int m_numberOfTiles;
  int calculateIndexToCollapseNext();
  bool checkIfTileFits(int pos, Tile tile);
  void enableSurroundingIndecesToBeChecked(int pos);
  void collapse();
};

#endif // HANDLER_H
