#include "numbers.h"


//========================================================================================
//NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE===NOTE
//========================================================================================
//FOR DOCUMENTATION AND EXPLANATION FOR SOME OF THE CALCULATIONS SEE BOTTOM OF THIS FILE
//========================================================================================
//ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE===ENDNOTE
//========================================================================================



Numbers::Numbers(int dimensionsWidth, int dimensionsHeight) :
    m_dimensionsWidth(dimensionsWidth),
    m_dimensionsHeight(dimensionsHeight),
    m_spacing(dimensionsWidth/19),
    m_lineSegmentWidth(3 * (dimensionsWidth/19))
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
    return QList<MapConstructor::constructParameters>() << this->getLineSegment(position,1,segmentWidth)
                                                        << this->getLineSegment(2,1,segmentWidth)
                                                        << this->getLineSegment(3,1,segmentWidth)
                                                        << this->getLineSegment(4,1,segmentWidth)





        ;
}
QList<MapConstructor::constructParameters> Numbers::getOne(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getTwo(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getThree(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFour(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFive(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSix(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSeven(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getEight(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getNine(int position, int segmentWidth){
    return QList<MapConstructor::constructParameters>();
}
//<<<---------------------------numbers------------------------------------

//-------------------------Functions to construct numbers------------------->>>
int Numbers::getStartingTileIndex(int position){
    switch (position){
    case 1: return m_spacing;
    case 2: return 2*m_spacing + m_lineSegmentWidth;
    case 3: return 5*m_spacing + 2*m_lineSegmentWidth;
    case 4: return 6*m_spacing + 3*m_lineSegmentWidth;
    default: return -1;
    }




}

MapConstructor::constructParameters Numbers::getLineSegment(int position, int index, int segmentWidth){

    int startingIndex =  this->getStartingTileIndex(position);
    switch(index){
    case 1: return MapConstructor::constructParameters(constructionStartIndexType::tileStartIndex,
                          startingIndex ,m_lineSegmentWidth,5,false,segmentWidth,constructionDirection::horizontal,true);
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    default: ;


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

                         width
        | ---------------------------|               s == spacing
        |                                             w == number width
        | |===| |===|   |===| |===|
        | |   | |   |   |   | |   |                 By defintion:(1) 3s = w
height  | |   | |   | o |   | |   |
        | |   | |   | o |   | |   |                 That yields: (2)7s + 4w = width
        | |   | |   |   |   | |   |                 (1) in (2)  <-> 7s + 12s = width
        | |===| |===|   |===| |===|                             <-> 19s      = width
        |^  ^        ^^^                            (3)         <-> width/19 = s
         |  |        |||                                        --> width must be multiple of 19
         s  w        sss                            (3) in (1)    3*width/19 = w








*/
//<<<-------------------------Function to construct numbers-------------------
