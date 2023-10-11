#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QThread>
#include "backenddatadto.h"
#include "collapser.h"

class GuiHandler : public QObject
{
    Q_OBJECT
      Q_PROPERTY (QList<int> tileMap READ getTileMap NOTIFY updateCanvas)
signals:
    void updateCanvas();

public:
    GuiHandler(){};
    GuiHandler(const BackendDataDto& dto);
    ~GuiHandler();
public slots:
    void drawGrid();
    void startCollapsing();
    //void tileMapChanged();

    int getDimensionsWidth() const { return m_collapser->getDimensionsWidth(); }
    int getDimensionsHeight() const {return m_collapser->getDimensionsHeight(); }
    int calculateTilePixelWidthHeight();
    QList<int> getTilesToHighlight() const {return m_collapser->getTilesToBeColouredDifferently();}
    QList<int> getTileMap() const{ return m_tileMap;}

private:
    int m_fps;
    QList<int> m_tileMap;

    QTimer *m_fpsTimer;
    QTimer *m_secondsTimer;
    int m_lastTime;
    Collapser *m_collapser;
    QThread *collapserThread;
    QList<MapConstructor::constructParameters> getCurrentTimeConstructParameters(const QTime& currentTime);
private slots:
    void onSecondsTimerTimeout();

};

#endif // GUIHANDLER_H
