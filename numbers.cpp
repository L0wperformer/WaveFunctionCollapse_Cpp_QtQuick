#include "numbers.h"

Numbers::Numbers()
{

}


QList<MapConstructor::constructParameters> Numbers::getNumberConstructParameters(int position, int number){
    //Origin index -> Top left coordinate of number. Every calculation will take this coordinate as reference.
    switch(number){
    case 0: return this->getZero(position); break;
    case 1: return this->getOne(position); break;
    case 2: return this->getTwo(position); break;
    case 3: return this->getThree(position); break;
    case 4: return this->getFour(position); break;
    case 5: return this->getFive(position); break;
    case 6: return this->getSix(position); break;
    case 7: return this->getSeven(position); break;
    case 8: return this->getEight(position); break;
    case 9: return this->getNine(position); break;
    default: return QList<MapConstructor::constructParameters>();
    }

}


//---------------------------------Numbers---------------------------->>>
QList<MapConstructor::constructParameters> Numbers::getZero(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getOne(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getTwo(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getThree(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFour(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getFive(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSix(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getSeven(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getEight(int position){
    return QList<MapConstructor::constructParameters>();
}
QList<MapConstructor::constructParameters> Numbers::getNine(int position){
    return QList<MapConstructor::constructParameters>();
}
//<<<---------------------------numbers------------------------------------

//-------------------------Function to construct numbers------------------->>>
MapConstructor::constructParameters getLineSegment(int position, int index){


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
