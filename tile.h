#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = nullptr);

signals:

};

#endif // TILE_H
