#ifndef HANDLER_H
#define HANDLER_H

#include "tile.h"
#include <QList>
#include <QSet>
#include <QObject>
#include <QElapsedTimer>

class Handler : public QObject {
  Q_OBJECT
public:
  Handler(QList<QList<int>> sockets, int dimensions, int m_numberOfTiles,
          QList<int> weights);

public slots:
  void drawGrid();
  void startCollapsing();
  int getDimensions() { return m_dimensions; }

signals:
  void gridInit();
  void drawTile(int posIndex, int newTileIndex);

private:
  QVector<int> *tileMap;
  QList<QList<int>> m_rules;
  QList<Tile> allTiles;
  QList<int> m_disadvantageWeights;
  QSet<int> m_indecesToCheck;
  int m_dimensions;
  int m_numberOfTiles;
  int calculateIndexToCollapseNext();
  bool checkIfTileFits(int pos, Tile tile);
  void enableSurroundingIndecesToBeChecked(int pos);
};

#endif // HANDLER_H
