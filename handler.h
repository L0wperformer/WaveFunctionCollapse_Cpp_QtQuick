#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Handler : public QObject {
  Q_OBJECT
public:
  Handler();

public slots:
  void drawGrid(char gridSize);
signals:
  void gridInit(char dimensions);
  void drawTile(char tileIndex);

private:
  QVector<QVector<char>> *tileMap;

  void test();
};

#endif // HANDLER_H
