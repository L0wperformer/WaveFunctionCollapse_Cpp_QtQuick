#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QObject>

class Tile : public QObject {
  Q_OBJECT
public:
  Tile(QList<int> edgeSockets);
  Tile(const Tile &copyThis);
  Tile(){};
  ~Tile(){};
  Tile &operator=(const Tile &rhs) {
    Q_UNUSED(rhs);
    return *this;
  };
  // Function to check if edge of other tile matches
  bool checkEdge(int side, QList<int> otherEdge);
  // 0 -> Top left, 1-> Top right...
  int getCornerSocket(int whichOne);
  // 0 -> Top , 1 -> Right, ...
  QList<int> getEdgeSockets(int sideIndex);

  // GetterSetter
  QList<int> getAllSockets() { return m_edgeSockets; }
  int getSocketsPerSide() { return socketsPerSide; }

private:
  // List defines what other tiles can connect to this tile
  QList<int> m_edgeSockets;
  int socketsPerSide;

signals:
};
// Q_DECLARE_METATYPE(Tile *);
#endif // TILE_H
