#include "numbers.h"

Numbers::Numbers()
{

}


QList<MapConstructor::constructParameters> Numbers::getNumberConstructParameters(int originIndex, int number){
    //Origin index -> Top left coordinate of number. Every calculation will take this coordinate as reference.
    switch(number){
    case 0: return this->getZero(originIndex); break;
    case 1: return this->getOne(originIndex); break;
    case 2: return this->getTwo(originIndex); break;
    case 3: return this->getThree(originIndex); break;
    case 4: return this->getFour(originIndex); break;
    case 5: return this->getFive(originIndex); break;
    case 6: return this->getSix(originIndex); break;
    case 7: return this->getSeven(originIndex); break;
    case 8: return this->getEight(originIndex); break;
    case 9: return this->getNine(originIndex); break;
    }

}


//---------------------------------Numbers---------------------------->>>
QList<MapConstructor::constructParameters> Numbers::getZero(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getOne(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getTwo(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getThree(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFour(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFive(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSix(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSeven(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getEight(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getNine(int originIndex){
    return QList<MapConstructor::constructParameters>();
}
//<<<---------------------------numbers------------------------------------

//-------------------------Function to construct numbers------------------->>>
MapConstructor::constructParameters getLineSegment(int originIndex, int index){
    /*========Line Segments:========
                    1
                   ===
               6  |   |  2
                  | 7 |
                   ===
               5  |   |  3
                  |   |
                   ===
                    4    */

}
//<<<-------------------------Function to construct numbers-------------------
