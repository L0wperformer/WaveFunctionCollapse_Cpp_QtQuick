#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Handler : public QObject{
    Q_OBJECT
public:
    Handler();
    void drawGrid(char gridSize);
private:
    QVector<QVector<char>> *tileMap;

    void test();
signals:
    void drawTile(char tileIndex);
};

#endif // HANDLER_H
