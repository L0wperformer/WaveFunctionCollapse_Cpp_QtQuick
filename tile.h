#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QList>

class Tile : public QObject
{
    Q_OBJECT
public:
    Tile(QList<char> edgeSockets);
    //Function to check if edge of other tile matches
    bool checkEdge(char side, QList<char> otherEdge);
    //0 -> Top , 1 -> Right, ...
    QList<char> getEdge(char sideIndex);
private:
    //List defines what other tiles can connect to this tile
    QList<char> m_edgeSockets;

    char socketsPerSide;

signals:

};

#endif // TILE_H
