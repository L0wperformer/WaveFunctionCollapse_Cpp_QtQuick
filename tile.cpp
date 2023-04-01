#include "tile.h"

Tile::Tile(const QList<int>& edgeSockets) {
  m_edgeSockets = edgeSockets;
  socketsPerSide = m_edgeSockets.length() / 4;
}

Tile::Tile(const Tile &copyThis) : QObject(nullptr) {
  m_edgeSockets = copyThis.m_edgeSockets;
  socketsPerSide = copyThis.socketsPerSide;
}

bool Tile::checkEdge(const int& side,const QList<int>& otherEdge) {

  QList<int> thisEdge = getEdgeSockets(side);

  for (int i = 0; i < otherEdge.length(); i++) {
    if (thisEdge.at(i) != otherEdge.at(i))
      return false;
  }

  return true;
}

  QList<int> Tile::getEdgeSockets(const int& sideIndex) const{
  int startIndex = socketsPerSide * sideIndex;
  QList<int> edgeSockets = m_edgeSockets.mid(startIndex, socketsPerSide);
  // Remove Corners
  edgeSockets.pop_front();
  edgeSockets.pop_back();
  return edgeSockets;
}

int Tile::getCornerSocket(const int& whichOne) const {
  return m_edgeSockets.at(whichOne * socketsPerSide);
}
