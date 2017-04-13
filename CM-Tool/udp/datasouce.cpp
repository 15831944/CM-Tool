/***
 * 1.提供随机变化的数据报souceData
 * 2.为外部提供获取souceData的接口getSouceData
 */
#include "datasouce.h"

DataSouce::DataSouce()
{

    allocateSpace();//分配空间
    updateSouceData();//更新数据
}

/**
 * @brief 更新数据源，当前值随机变化，阈值可被外界修改
 */
void DataSouce::updateSouceData()
{

    initElectricData(souceData->loopData);
    //    qDebug()<<"电流当前值："<<*(souceData->loopData.cur.currentValue);
    initElectricData(souceData->inputPhrase);
    qDebug()<<"输入相电流数据：";
    qDebug()<<*(souceData->loopData.cur.currentValue);
    qDebug()<<*(souceData->loopData.cur.minValue);
    qDebug()<<*(souceData->loopData.cur.maxValue);
    qDebug()<<*(souceData->loopData.cur.alarmValue);
    qDebug()<<*(souceData->loopData.cur.cirMinValue);
    qDebug()<<*(souceData->loopData.cur.cirMaxValue);
    qDebug()<<*(souceData->loopData.cur.cirAlarmValue);

    initElectricData(souceData->outData);

}

/**
 * @brief 传入基数和范围，获取某个范围的随机数，用于控制电流及当前电压范围
 * @param baseNum
 * @param socpe
 */

template <class T> void DataSouce::initRandomBuf(T baseNum , T socpe, T *buf)
{

    //    qDebug()<<"initRandomBuf";
    //    qDebug()<<"data.currentValue:"<<buf;
    //    quint16 *buffer = new quint16[32];
    //    buf = new quint16[32];

    for(int i = 0 ; i < 32 ; i++)
    {
        //        buffer[i] = baseNum + Random(socpe);//获取一个在1到5（即1+4）之间的随机数
        *(buf+i) = baseNum + Random(socpe);//获取一个在1到5（即1+4）之间的随机数

        //        qDebug()<<"buf:"<<*(buf + i);
    }
    //    buf = buffer;

}



/**
 * @brief 用于阈值等的统一初始化
 * @param num
 * @return
 */
template <class T> void DataSouce::initFixedBuf(T num , T *buf)
{
    //    qDebug()<<"initFixedBuf";
    //    quint16 *buf = new quint16[32];
    for(int i = 0 ; i < 32 ; i++)
    {
        *(buf+i) = num;
    }

}


/**
 * @brief 为初始数据分配空间，只初始化一次
 * @param data
 */
void DataSouce::initElectricDataSpace(electricData &data)
{
    initUnitSpace(data.cur);
    initUnitSpace(data.vol);

    data.power = new quint32[32];
    data.energy = new quint32[32];
    data.powerFactor = new quint16[32];
    data.switchStatus = new quint8[32];
    data.cDrined = new quint16[32];
    data.voltagefrequency = new quint16[32];
}


/**
 * @brief 初始化电气数据，包括回路、相及输出位数据
 * @param data
 */
void DataSouce::initElectricData(electricData &data)
{
    //    qDebug()<<"initElectricData";
    initUnit(data.cur);
    initUnit(data.vol);

    initRandomBuf<quint32>(200,300,data.power);
    initRandomBuf<quint32>(400,500,data.energy);
    initRandomBuf<quint16>(1,2,data.powerFactor);
    initRandomBuf<quint8>(0,1,data.switchStatus); //开关范围为0 - 1
    initRandomBuf<quint16>(500,500,data.cDrined);
    initRandomBuf<quint16>(10,10,data.voltagefrequency);
    data.len = 6;

}

/**
 * @brief 为初始数据分配空间，只初始化一次
 * @param data
 */
void DataSouce::initUnitSpace(unit &data)
{
    data.currentValue = new quint16[32];
    data.minValue = new quint16[32];
    data.maxValue = new quint16[32];
    data.alarmValue = new quint8[32];
    data.cirMinValue = new quint16[32];
    data.cirMaxValue = new quint16[32];
    data.cirAlarmValue = new quint8[32];
}

/**
 * @brief 初始化电流电压数据
 * @param data
 */
void DataSouce::initUnit(unit &data)
{
    //    qDebug()<<"initUnit";
    //    qDebug()<<"data.currentValue:"<<data.currentValue;
    initRandomBuf<quint16>(10,15,data.currentValue);

    //    qDebug()<<"data.currentvalue:"<<*(data.currentValue);


    initFixedBuf<quint16>(5,data.minValue);
    initFixedBuf<quint16>(7,data.maxValue);
    initFixedBuf<quint8>(8,data.alarmValue);
    initFixedBuf<quint16>(26,data.cirMinValue);
    initFixedBuf<quint16>(28,data.cirMaxValue);
    initFixedBuf<quint8>(30,data.cirAlarmValue);
    data.num = 24;
}

/**
 * @brief 通过该接口可以获取原始数据
 * @return
 */
parameterData *DataSouce::getSouceData()
{

    return souceData;
}

/**
 * @brief 为源数据分配内存空间
 */
void DataSouce::allocateSpace()
{
    souceData = new parameterData; //为初始化数据申请空间存储
    initElectricDataSpace(souceData->loopData);
    initElectricDataSpace(souceData->inputPhrase);
    initElectricDataSpace(souceData->outData);

}








