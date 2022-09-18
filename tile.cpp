#include "tile.h"

Tile::Tile(QList<char> edgeSockets)
{
    m_edgeSockets = edgeSockets;
    socketsPerSide = m_edgeSockets.length() / 4 ;
}

bool Tile::checkEdge(char side, QList<char> otherEdge){

    QList<char> thisEdge = getEdge(side);

    for (int i = 0; i < otherEdge.length(); i++)  {
         if(thisEdge.at(i) != otherEdge.at(i))
             return false;
    }

    return true;
  }

QList<char> Tile::getEdge(char sideIndex){

    char startIndex = socketsPerSide * sideIndex;

    return m_edgeSockets.mid(startIndex,socketsPerSide);

}
