#ifndef NUMBERS_H
#define NUMBERS_H

#include <QObject>
#include "mapconstructor.h"

class Numbers : public QObject
{
    Q_OBJECT
public:
    Numbers();
    QList<MapConstructor::constructParameters> getNumberConstructParameters(int originIndex, int number);
private:
    QList<MapConstructor::constructParameters> getZero(int originIndex);
    QList<MapConstructor::constructParameters> getOne(int originIndex);
    QList<MapConstructor::constructParameters> getTwo(int originIndex);
    QList<MapConstructor::constructParameters> getThree(int originIndex);
    QList<MapConstructor::constructParameters> getFour(int originIndex);
    QList<MapConstructor::constructParameters> getFive(int originIndex);
    QList<MapConstructor::constructParameters> getSix(int originIndex);
    QList<MapConstructor::constructParameters> getSeven(int originIndex);
    QList<MapConstructor::constructParameters> getEight(int originIndex);
    QList<MapConstructor::constructParameters> getNine(int originIndex);
    MapConstructor::constructParameters getLineSegment(int originIndex, int index);

};

#endif // NUMBERS_H
