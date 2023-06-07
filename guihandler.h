#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include <QTimer>
#include "backenddatadto.h"

class GuiHandler : public QObject
{
    Q_OBJECT
signals:
    void updateCanvas();

public:
    GuiHandler(){};
    GuiHandler(const BackendDataDto& dto);
public slots:
    void drawGrid();
    void startCollapsing();


    int getDimensionsWidth() { return m_dimensionsWidth; }
    int getDimensionsHeight() {return m_dimensionsHeight; }
    QList<int> getTilesToHighlight() {return m_tilesToBeColoredDifferently;}
    QList<int> getTileMap() const{
        return (*tileMap);
    }

private:
    QTimer *fpsTimer;
private:

};

#endif // GUIHANDLER_H
