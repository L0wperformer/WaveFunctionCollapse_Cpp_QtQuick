#ifndef NUMBERS_H
#define NUMBERS_H

#include <QObject>
#include "mapconstructor.h"

class Numbers : public QObject
{
    Q_OBJECT
public:
    Numbers();
    QList<MapConstructor::constructParameters> getNumberConstructParameters(int position, int number);
private:
    QList<MapConstructor::constructParameters> getZero(int position);
    QList<MapConstructor::constructParameters> getOne(int position);
    QList<MapConstructor::constructParameters> getTwo(int position);
    QList<MapConstructor::constructParameters> getThree(int position);
    QList<MapConstructor::constructParameters> getFour(int position);
    QList<MapConstructor::constructParameters> getFive(int position);
    QList<MapConstructor::constructParameters> getSix(int position);
    QList<MapConstructor::constructParameters> getSeven(int position);
    QList<MapConstructor::constructParameters> getEight(int position);
    QList<MapConstructor::constructParameters> getNine(int position);
    MapConstructor::constructParameters getLineSegment(int position, int index);

};

#endif // NUMBERS_H
