#include "handler.h"
#include "tile.h"
#include <QDebug>

Handler::Handler()
{
test();
}

void Handler::test(){

    QList<char> teilEinsKante = {0,0,0,
                                     0,1,0,
                                     0,0,0,
                                     0,0,0};

    QList<char> teilZweiKante = {0,1,0,
                                     0,1,0,
                                     0,1,0,
                                     0,1,0};

    Tile teilEins(teilEinsKante);
    Tile teilZwei(teilZweiKante);

    qDebug() << teilEins.checkEdge(1,teilZwei.getEdge(3));






}
