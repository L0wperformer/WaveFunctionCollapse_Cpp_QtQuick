#include "tile.h"

Tile::Tile(QList<int> edgeSockets) {
  m_edgeSockets = edgeSockets;
  socketsPerSide = m_edgeSockets.length() / 4;
}

Tile::Tile(const Tile &copyThis) : QObject(nullptr) {
  m_edgeSockets = copyThis.m_edgeSockets;
  socketsPerSide = copyThis.socketsPerSide;
}

bool Tile::checkEdge(int side, QList<int> otherEdge) {

  QList<int> thisEdge = getEdge(side);

  for (int i = 0; i < otherEdge.length(); i++) {
    if (thisEdge.at(i) != otherEdge.at(i))
      return false;
  }

  return true;
}

QList<int> Tile::getEdge(int sideIndex) {

  int startIndex = socketsPerSide * sideIndex;
  return m_edgeSockets.mid(startIndex, socketsPerSide);
}
