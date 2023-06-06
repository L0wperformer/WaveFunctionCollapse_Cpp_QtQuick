#include "mapconstructor.h"

MapConstructor::MapConstructor(const QList<constructParameters>& params,
                               const int& dimensionsWidth,
                               const int& dimensionsHeight):
    m_params(params),
    m_dimensionsWidth(dimensionsWidth),
    m_dimensionsHeight(dimensionsHeight){

    m_dimensionsWidthHeight = m_dimensionsWidth*m_dimensionsHeight;
    m_weightMap = QVector<int> (m_dimensionsHeight*m_dimensionsWidth,0).toList();
}

QList<int> MapConstructor::constructWeightmap(){
    for (const auto& item : m_params) {//This is ugly
        int startIndex = -1;
        switch(item.indexType){
        case constructionStartIndexType::columnStartIndex:
            //column start cant be greater than width
            //Well.. Lets catch that
            startIndex = item.startIndex;
            break;
        case constructionStartIndexType::lineStartIndex:
            startIndex = m_dimensionsWidth * item.startIndex;
            break;
        case constructionStartIndexType::tileStartIndex:
            startIndex = item.startIndex;
            break;
        }

        int stepSize = -1;
        switch(item.direction){
        case constructionDirection::horizontal:
            stepSize = 1;
            break;
        case constructionDirection::vertical:
            stepSize = m_dimensionsWidth;
            break;
        }

        int endIndex = startIndex;
        if(item.applyLength != -1){
            endIndex = startIndex + item.applyLength * stepSize;
        }

        if(item.applyLength == -1 && item.jumpLinesColumns){
            endIndex = m_dimensionsWidthHeight -1;
        }

        if(item.applyLength == -1 && !item.jumpLinesColumns){
            switch(item.direction){ //Ew, Nesting
            case constructionDirection::horizontal:
                while((endIndex+1) % m_dimensionsWidth != 0)
                    endIndex++;
                break;

            case constructionDirection::vertical:
                while(true){
                    if(endIndex + m_dimensionsWidth > m_dimensionsWidthHeight -1 ) //Eeeeeeeeeewwwww, Nesting
                        break;
                    endIndex += m_dimensionsWidth;
                }
                break;
            }

        }

        int increaseIndex = -1;
        switch(item.direction){ //you again
        case constructionDirection::horizontal:
            increaseIndex = m_dimensionsWidth;
            break;
        case constructionDirection::vertical:
            increaseIndex = 1;
            break;
        }


        for(int i = 0; i < item.applyToHowManyConsecutiveLinesColumns; i++)
            for( int j = startIndex + increaseIndex*i ; j < endIndex+ increaseIndex*i; j += stepSize ){
//                if(item.applyHighlight)
//                    m_tilesToBeColoredDifferently.append(j);
                m_weightMap.replace(j,item.tileOrWeightMapIndex);
            }


    }

    return m_weightMap;
}

QList<int> MapConstructor::getTilesAffectedByMap(){
    QList<int> returnThis;
    for (int i = 0 ; i< m_weightMap.length() ; i++)
        if(m_weightMap.at(i) != 0)
            returnThis.append(i);

    return returnThis;
}

