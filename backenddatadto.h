#ifndef BACKENDDATADTO_H
#define BACKENDDATADTO_H

#include <QObject>
#include "mapconstructor.h"

class BackendDataDto
{
    Q_OBJECT
public:
    BackendDataDto(){};
    BackendDataDto(const QList<QList<int>>& sockets,
                   const int& dimensionsWidth,
                   const int& dimensionsHeight,
                   const int& numberOfTiles,
                   const QList<MapConstructor::constructParameters>& precollapedTilesConstructionInstructions ,
                   const QList<MapConstructor::constructParameters>& weightmapConstructionInstructions,
                   const QList<QList<int>>& availableWeightLists);
public:
QList<QList<int>> m_sockets;
int m_dimensionsWidth;
int m_dimensionsHeight;
int m_numberOfTiles;
QList<MapConstructor::constructParameters> m_precollapsedTilesConstructionInstructions;
QList<MapConstructor::constructParameters> m_weightmapConstructionInstructions;
QList<QList<int>> m_availableWeightLists;

};

#endif // BACKENDDATADTO_H
