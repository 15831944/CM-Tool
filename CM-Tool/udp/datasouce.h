#ifndef DATASOUCE_H
#define DATASOUCE_H

#define Random(x) (rand() % x) //获取0到x之间的随机数

#include "datadefine.h"
//#include "mainwindow.h"
#include <QDebug>

typedef struct deviceSettings
{
    uchar devType; //1 -ip  2 -rp  3 -mp
    QString devName;
    uchar viceNumber;
    int devLoopNum;
    int devPhaseNum;
    int devOutNum;
    int devSensorNum;
    quint8 entranceGuard1;
    quint8 entranceGuard2;
    quint8 smoke;
    quint8 water;


}devSetings;


class DataSouce
{
public:
    DataSouce();
    ~DataSouce();


public:


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

    //提供修改原始数据的接口
    void setData(unit *mUnit, int num, quint8 *data);
    //    void setData(unit *mUnit, int num, quint16 *data);

    void renewalSouceData(); //更新数据
    void renewalUnit(unit &mUnit);

    void changeDevSettings();

private:
    parameterData *souceData;





};

extern DataSouce *get_datasouce();
extern devSetings *get_devsetings();

#endif // DATASOUCE_H
