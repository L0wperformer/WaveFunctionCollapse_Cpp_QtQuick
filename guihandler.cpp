#include "guihandler.h"
#include "numbers.h"
#include <QThread>
#include <QDebug>
#include <QTime>

GuiHandler::GuiHandler(const BackendDataDto& dto){
    m_fpsTimer = new QTimer(this);
    connect(m_fpsTimer, &QTimer::timeout,this, &GuiHandler::updateCanvas);
    m_fps = 60;
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


    //QTimer::singleShot(10, this, &GuiHandler::startCollapsing);
}

void GuiHandler::drawGrid(){
    emit updateCanvas();
}

QList<MapConstructor::constructParameters> GuiHandler::getCurrentTimeConstructParameters(const QTime& currentTime){

    Numbers numbers(100,50);
    QList<MapConstructor::constructParameters> disadvantageWeightmapConstructionInstructions;
    qDebug() << (currentTime.hour()/10)%10 << currentTime.hour()%10 << (currentTime.minute()/10)%10 << currentTime.minute()%10;
    disadvantageWeightmapConstructionInstructions << numbers.getNumberConstructParameters(1,(currentTime.hour()/10)%10,3)
                                                  << numbers.getNumberConstructParameters(2,currentTime.hour()%10,3)
                                                  << numbers.getNumberConstructParameters(3,(currentTime.minute()/10)%10,3)
                                                  << numbers.getNumberConstructParameters(4,(currentTime.minute()%10),3);//numberWeightmapOne;//numberWeightmapTwo;
    return    disadvantageWeightmapConstructionInstructions;
}

void GuiHandler::startCollapsing(){
    qDebug() << "Starting Collapse Algorithm";
    QTime currentTime(QTime::currentTime());
    m_collapser->setNewWeightMap(this->getCurrentTimeConstructParameters(currentTime));
    m_fpsTimer->start(1000/m_fps);
    collapserThread->start();
    m_secondsTimer->start(1000);
//    int currentHour = -1;



}

void GuiHandler::onSecondsTimerTimeout(){

        QTime currentTime(QTime::currentTime());

       if(m_lastTime == currentTime.minute())
            return;


       m_collapser->setNewWeightMap(this->getCurrentTimeConstructParameters(currentTime));
       //m_collapser->restart();
       m_lastTime = currentTime.minute();
}

GuiHandler::~GuiHandler(){
    delete m_fpsTimer;
    delete m_collapser;
}
