#include "backenddatadto.h"

BackendDataDto::BackendDataDto(const QList<QList<int>>& sockets,
                               const int& dimensionsWidth,
                               const int& dimensionsHeight,
                               const int& windowSizeHorizontalInPixels,
                               const int& numberOfTiles,
                               const QList<MapConstructor::constructParameters>& precollapedTilesConstructionInstructions ,
                               const QList<MapConstructor::constructParameters>& weightmapConstructionInstructions,
                               const QList<QList<int>>& availableWeightLists):
    m_sockets(sockets),
    m_dimensionsWidth(dimensionsWidth),
    m_dimensionsHeight(dimensionsHeight),
    m_numberOfTiles(numberOfTiles),
    m_precollapsedTilesConstructionInstructions(precollapedTilesConstructionInstructions),
    m_weightmapConstructionInstructions(weightmapConstructionInstructions),
    m_availableWeightLists(availableWeightLists),
    m_windowSizeHorizontalInPixels(windowSizeHorizontalInPixels)
{}
