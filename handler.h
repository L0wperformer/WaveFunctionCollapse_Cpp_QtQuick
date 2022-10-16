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
  Handler(QList<QList<int>> sockets, int dimensions, int m_numberOfTiles,
          QList<int> weights);


public slots:
  void drawGrid();
  void startCollapsing();


  int getDimensions() { return m_dimensions; }
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
  QSet<int> m_indecesToCheck;
  int m_dimensions;
  int m_numberOfTiles;
  int calculateIndexToCollapseNext();
  bool checkIfTileFits(int pos, Tile tile);
  void enableSurroundingIndecesToBeChecked(int pos);
  void collapse();
};

#endif // HANDLER_H
