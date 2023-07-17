#ifndef NUMBERS_H
#define NUMBERS_H

#include <QObject>
#include "mapconstructor.h"

class Numbers : public QObject
{
    Q_OBJECT
public:
    Numbers() = delete;
    Numbers(int dimensionsWidth, int dimensionsHeight);
    QList<MapConstructor::constructParameters> getNumberConstructParameters(int position, int number, int segmentWidth);
private:
    QList<MapConstructor::constructParameters> getZero(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getOne(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getTwo(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getThree(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getFour(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getFive(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getSix(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getSeven(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getEight(int position, int segmentWidth);
    QList<MapConstructor::constructParameters> getNine(int position, int segmentWidth);
    MapConstructor::constructParameters getLineSegment(int position, int index, int segmentWidth);

private:
    int m_dimensionsWidth;
    int m_dimensionsHeight;

};

#endif // NUMBERS_H
