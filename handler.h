#ifndef HANDLER_H
#define HANDLER_H

#include "tile.h"
#include <QList>
#include <QSet>
#include <QObject>
#include <QElapsedTimer>
#include <QQuickView>

class Handler : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVector<QObject*> tileMap READ getTileMap NOTIFY tileMapChanged)
public:
  Handler(QList<QList<int>> sockets, int dimensions, int m_numberOfTiles,
          QList<int> weights);

public slots:
  void drawGrid();
  void startCollapsing();


  int getDimensions() { return m_dimensions; }
  QVector<QObject*> getTileMap(){
      return (*objectTileMap);
  }


signals:
  void gridInit();
  void tileMapChanged();
  //void drawTile(int pos, int index)


private:
  QVector<int> *tileMap;
  QVector<QObject*>  *objectTileMap;
  QList<QList<int>> m_rules;
  QList<Tile> allTiles;
  QList<int> m_disadvantageWeights;
  QSet<int> m_indecesToCheck;
  int m_dimensions;
  int m_numberOfTiles;
  int calculateIndexToCollapseNext();
  bool checkIfTileFits(int pos, Tile tile);
  void enableSurroundingIndecesToBeChecked(int pos);
  void drawTile(int pos, int index);
};

#endif // HANDLER_H
