#ifndef DATASOUCE_H
#define DATASOUCE_H

#define Random(x) (rand() % x) //获取0到x之间的随机数

#include "datadefine.h"
#include <QDebug>


//template<typename T> void swap(T& t1, T& t2);

class DataSouce
{
public:
    DataSouce();


public:
    parameterData *souceData;

    void updateSouceData();

    template<typename T> void initRandomBuf(T baseNum , T socpe, T *buf);
    //    void initRandomBufquint(quint8 baseNum, quint8 socpe, quint8 *buf);

    template<typename T>  void initFixedBuf(T num , T *buf);
    //    void initFixedBufquint(int num , quint8 *buf);

    void initElectricData(electricData &data);
    void initElectricDataSpace(electricData &data);
    void initUnit(unit &data);
    void initUnitSpace(unit &data);
    parameterData *getSouceData();
    void allocateSpace();




};

#endif // DATASOUCE_H
