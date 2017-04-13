#ifndef DATADEFINE_H
#define DATADEFINE_H

#include <qglobal.h>

typedef struct dataUnit{
    quint16 *currentValue;
    quint16 *minValue;
    quint16 *maxValue;
    quint8 *alarmValue;
    quint16 *cirMinValue;
    quint16 *cirMaxValue;
    quint8 *cirAlarmValue; //临界报警状态
    quint8 num;  //数量
}unit;

typedef struct circuitParameters
{
    int len; //长度，定义功率因数等数量
    unit cur;
    unit vol;
    quint32  *power;
    quint32 *energy;
    quint16 *powerFactor;
    quint8 *switchStatus;
    quint16 *cDrined; //排c量
    quint16 *voltagefrequency; //电压频率
}electricData;


typedef struct loopOutPhrase
{
    electricData loopData;

    electricData inputPhrase;
    electricData outData;

}parameterData;



#endif // DATADEFINE_H
