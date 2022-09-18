#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Handler : public QObject{
    Q_OBJECT
public:
    Handler();
    void createGrid(char gridSize);
private:
    void test();
};

#endif // HANDLER_H
