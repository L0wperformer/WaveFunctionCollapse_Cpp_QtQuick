#include "numbers.h"


//========================================================================================
//NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE
//========================================================================================
//FOR DOCUMENTATION AND EXPLANATION FOR SOME OF THE CALCULATIONS SEE BOTTOM OF THIS FILE
//========================================================================================
//ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE
//========================================================================================



Numbers::Numbers(int dimensionsWidth, int dimensionsHeight, bool highlight) :
    m_dimensionsWidth(dimensionsWidth),
    m_dimensionsHeight(dimensionsHeight),
    m_spacing(dimensionsWidth/19),
    m_lineSegmentWidth(3 * (dimensionsWidth/19)),
    m_highlight(highlight)
{

}


QList<MapConstructor::constructParameters> Numbers::getNumberConstructParameters(int position, int number, int segmentWidth){
    //Origin index -> Top left coordinate of number. Every calculation will take this coordinate as reference.
    switch(number){
    case 0: return this->getZero(position, segmentWidth); break;
    case 1: return this->getOne(position, segmentWidth); break;
    case 2: return this->getTwo(position, segmentWidth); break;
    case 3: return this->getThree(position, segmentWidth); break;
    case 4: return this->getFour(position, segmentWidth); break;
    case 5: return this->getFive(position, segmentWidth); break;
    case 6: return this->getSix(position, segmentWidth); break;
    case 7: return this->getSeven(position, segmentWidth); break;
    case 8: return this->getEight(position, segmentWidth); break;
    case 9: return this->getNine(position, segmentWidth); break;
    default: return QList<MapConstructor::constructParameters>();
    }

}


//---------------------------------Numbers---------------------------->>>
QList<MapConstructor::constructParameters> Numbers::getZero(int position, int segmentWidth){

//    QList<MapConstructor::constructParameters> returnThis;
//    for (int i = 1; i < 5 ; i++){
////        returnThis << this->getLineSegment(i,i,segmentWidth);
//        returnThis << this->getLineSegment(i,3,segmentWidth);

//    }

//    return returnThis;

    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth)
                                                            << this->getLineSegment(position, 5,segmentWidth)
                                                            << this->getLineSegment(position, 6,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getOne(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>() << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getTwo(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth)
                                                            << this->getLineSegment(position, 5,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getThree(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getFour(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 6,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth);
        ;
}
QList<MapConstructor::constructParameters> Numbers::getFive(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 6,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getSix(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 6,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth)
                                                            << this->getLineSegment(position,5,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getSeven(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getEight(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth)
                                                            << this->getLineSegment(position, 5,segmentWidth)
                                                            << this->getLineSegment(position, 6,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth);
}
QList<MapConstructor::constructParameters> Numbers::getNine(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>()<< this->getLineSegment(position, 1,segmentWidth)
                                                            << this->getLineSegment(position, 2,segmentWidth)
                                                            << this->getLineSegment(position, 3,segmentWidth)
                                                            << this->getLineSegment(position, 4,segmentWidth)
                                                            << this->getLineSegment(position, 6,segmentWidth)
                                                            << this->getLineSegment(position, 7,segmentWidth);
}
//<<<---------------------------numbers------------------------------------

//-------------------------Functions to construct numbers------------------->>>
int Numbers::getStartingTileIndex(int horizontalPosition, int verticalPosition, int index){
    int startingIndex = 0;
    switch (horizontalPosition){
    case 1: startingIndex =  m_spacing; break;
    case 2: startingIndex =  2*m_spacing + m_lineSegmentWidth; break;
    case 3: startingIndex =  5*m_spacing + 2*m_lineSegmentWidth; break;
    case 4: startingIndex =  6*m_spacing + 3*m_lineSegmentWidth; break;
    default: return -1;
    }

    switch (verticalPosition){
    case 1: startingIndex +=  2*m_spacing*m_dimensionsWidth;break;
    case 2: startingIndex +=  5*m_spacing*m_dimensionsWidth;break;
    case 3: startingIndex += 8*m_spacing*m_dimensionsWidth;break;
    default: return -1;
    }

    if(index == 2){
        startingIndex += m_lineSegmentWidth;
    }

    if(index == 3){
        startingIndex += m_lineSegmentWidth ;//+ /*(int)0.5**/m_spacing*m_dimensionsWidth;
    }

    return startingIndex;

}

MapConstructor::constructParameters Numbers::getLineSegment(int position, int index, int segmentWidth){

    switch(index){
    case 1: return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,//Done
                          this->getStartingTileIndex(position,1,index) ,m_lineSegmentWidth  + segmentWidth,6,false,segmentWidth,constructionDirection::horizontal,m_highlight);
    case 2:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,
                          this->getStartingTileIndex(position,1,index) ,m_lineSegmentWidth  + segmentWidth/*+ 0.5*m_spacing*/,5,false,segmentWidth,constructionDirection::vertical,m_highlight);
    case 3:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,
                          this->getStartingTileIndex(position,2,index) ,m_lineSegmentWidth  + segmentWidth,5,false,segmentWidth,constructionDirection::vertical,m_highlight);
    case 4:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,//Done
                          this->getStartingTileIndex(position,3,index) ,m_lineSegmentWidth  + segmentWidth,6,false,segmentWidth,constructionDirection::horizontal,m_highlight);
    case 5:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,
                          this->getStartingTileIndex(position,2,index) ,m_lineSegmentWidth  + segmentWidth,5,false,segmentWidth,constructionDirection::vertical,m_highlight);
    case 6:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,
                          this->getStartingTileIndex(position,1,index) ,m_lineSegmentWidth  + segmentWidth,5,false,segmentWidth,constructionDirection::vertical,m_highlight);
    case 7:return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,//Done
                           this->getStartingTileIndex(position,2,index)  ,m_lineSegmentWidth + segmentWidth,6,false,segmentWidth,constructionDirection::horizontal,m_highlight);
    case 8: //POINTS TODO
    default:  ;


    }





}


/*========Line Segments:========
 * in case I ever install it
//clang-format off
                    1
                   ===
               6  |   |  2
                  | 7 |
                   ===
               5  |   |  3
                  |   |
                   ===
                    4


Canvas calculations:



Hori-
zontal->          1     2        3    4
pos.
-------
vert.           width
pos.         | ---------------------------|               s == spacing
             |                               s              w == number width
 1           | |===| |===|   |===| |===|     s
             | |   | |   |   |   | |   |     s            By defintion:(1) 3s = w
2    height  | |   | |   | o |   | |___|     s
             | |   | |   | o |   | |   |     s            That yields: (2)7s + 4w = width
             | |   | |   |   |   | |   |     s            (1) in (2)  <-> 7s + 12s = width
 3           | |===| |===|   |===| |===|                             <-> 19s      = width
             |^  ^        ^^^                            (3)         <-> width/19 = s
              |  |        |||                                        --> width must be multiple of 19
              s  w        sss                            (3) in (1)    3*width/19 = w








*/
//<<<-------------------------Function to construct numbers-------------------
