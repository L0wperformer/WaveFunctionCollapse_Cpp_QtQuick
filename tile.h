#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QObject>

class Tile : public QObject {
  Q_OBJECT
public:
  Tile(QList<int> edgeSockets);
  // Function to check if edge of other tile matches
  bool checkEdge(int side, QList<int> otherEdge);
  // 0 -> Top , 1 -> Right, ...
  QList<int> getEdge(int sideIndex);

private:
  // List defines what other tiles can connect to this tile
  QList<int> m_edgeSockets;

  char socketsPerSide;

signals:
};

#endif // TILE_H
