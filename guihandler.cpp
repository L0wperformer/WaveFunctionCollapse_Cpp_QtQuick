#include "guihandler.h"
#include "numbers.h"
#include <QThread>
#include <QDebug>
#include <QTime>

GuiHandler::GuiHandler(const BackendDataDto& dto){
    m_fpsTimer = new QTimer(this);
    connect(m_fpsTimer, &QTimer::timeout,this, &GuiHandler::updateCanvas);
    m_fps = dto.m_fps;
    m_collapser = new Collapser(dto);
    collapserThread = new QThread(this);
    m_collapser->moveToThread(collapserThread);
    m_tileMap = QVector<int>(dto.m_dimensionsWidth* dto.m_dimensionsHeight,-1).toList();
    connect(collapserThread, &QThread::finished, collapserThread, &QThread::deleteLater);
    connect(collapserThread,&QThread::started,m_collapser,&Collapser::startCollapsing);
    connect(m_collapser, &Collapser::tileMapChanged,this,[&](int index, int newTile){
        m_tileMap.replace(index, newTile);
    });

    m_secondsTimer = new QTimer(this);
    connect(m_secondsTimer, &QTimer::timeout, this, &GuiHandler::onSecondsTimerTimeout );

    connect(m_collapser, &Collapser::updateCanvas, this, &GuiHandler::updateCanvas);

    m_numbers = new Numbers(dto.m_dimensionsWidth, dto.m_dimensionsHeight);
    //QTimer::singleShot(10, this, &GuiHandler::startCollapsing);
}

void GuiHandler::drawGrid(){
    emit updateCanvas();
}

QList<MapConstructor::constructParameters> GuiHandler::getCurrentTimeConstructParameters(const QTime& currentTime){


    QList<MapConstructor::constructParameters> disadvantageWeightmapConstructionInstructions;
    qDebug() << (currentTime.hour()/10)%10 << currentTime.hour()%10 << (currentTime.minute()/10)%10 << currentTime.minute()%10;
    disadvantageWeightmapConstructionInstructions << m_numbers->getNumberConstructParameters(1,(currentTime.hour()/10)%10,3)
                                                  << m_numbers->getNumberConstructParameters(2,currentTime.hour()%10,3)
                                                  << m_numbers->getNumberConstructParameters(3,(currentTime.minute()/10)%10,3)
                                                  << m_numbers->getNumberConstructParameters(4,(currentTime.minute()%10),3);//numberWeightmapOne;//numberWeightmapTwo;
    return    disadvantageWeightmapConstructionInstructions;
}

void GuiHandler::startCollapsing(){
    qDebug() << "Starting Collapse Algorithm";
    QTime currentTime(QTime::currentTime());
    m_collapser->setNewWeightMap(this->getCurrentTimeConstructParameters(currentTime));
    emit tilesToHighlightChanged(m_collapser->getTilesToBeColouredDifferently());
    m_fpsTimer->start(1000/m_fps);
    collapserThread->start();
    m_secondsTimer->start(1000);
//    int currentHour = -1;



}
int GuiHandler::calculateTilePixelWidthHeight(){
    int horizontalPixels = m_collapser->getWindowSizeHorizontalInPixels();
    int horizontalTiles = m_collapser->getDimensionsWidth();
    //CURRENTLY WIDTH MUST BE GREATER THAN HEIGHT
    if(horizontalTiles < m_collapser->getDimensionsWidth()){
        //Sorry
        qFatal("Width must have more or equal number of tiles as height");
        return -1;
    }

    while((horizontalPixels%horizontalTiles) != 0){
        horizontalPixels--;
    }

    qDebug() << "Pixels in horizontal direction: " << horizontalPixels;
    return horizontalPixels/horizontalTiles;

}

void GuiHandler::onSecondsTimerTimeout(){

        QTime currentTime(QTime::currentTime());

       if(m_lastTime == currentTime.minute())
            return;

       m_collapser->resetTileMap();
       m_collapser->setNewWeightMap(this->getCurrentTimeConstructParameters(currentTime));
       emit tilesToHighlightChanged(m_collapser->getTilesToBeColouredDifferently());
       //m_collapser->restart();
       m_lastTime = currentTime.minute();
}

GuiHandler::~GuiHandler(){
    delete m_fpsTimer;
    delete m_collapser;
    delete m_numbers;
}
