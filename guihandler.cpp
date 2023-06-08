#include "guihandler.h"
#include <QThread>
#include <QDebug>

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

}

void GuiHandler::drawGrid(){
    emit updateCanvas();
}

void GuiHandler::startCollapsing(){
    qDebug() << "Starting Collapse Algorithm";
    m_fpsTimer->start(1000/m_fps);
    collapserThread->start();
}

GuiHandler::~GuiHandler(){
    delete m_fpsTimer;
    delete m_collapser;
}
