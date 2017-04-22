/***
 * 1.提供随机变化的数据报souceData
 * 2.为外部提供获取souceData的接口getSouceData
 */
#include "datasouce.h"

static DataSouce *souce =NULL;

DataSouce *get_datasouce()
{
    if(!souce)
    {
        souce = new DataSouce;
        //        qDebug()<<"get_HeartBeat";
    }
//    qDebug() <<<<souce;
    for(int i = 0 ; i < 6 ;i++)
    qDebug() << "get_datasouce:" <<i<<*(souce->getSouceData()->loopData.switchStatus+i);
    return  souce;
}


DataSouce::DataSouce()
{

    allocateSpace();//分配空间
    updateSouceData();//更新数据
}

DataSouce::~DataSouce()
{


}

/**
 * @brief 更新数据源，当前值随机变化，阈值可被外界修改
 */
void DataSouce::updateSouceData()
{
    //为回路、输出位、输入相初始化数据
    initElectricData(souceData->loopData);
    for(int i = 0 ; i < 6 ;i++)
    qDebug() << "loop:" <<i<<*(souceData->loopData.switchStatus+i);

    initElectricData(souceData->inputPhrase);

    initElectricData(souceData->outData);
     for(int i = 0 ; i < 6 ;i++)
    qDebug() << "out:" <<i<<*(souceData->outData.switchStatus+i);

    //为环境数据初始化数据
    initUnit(souceData->envData.tem);
    initUnit(souceData->envData.hum);

    initRandomBuf<quint8>(0,1,souceData->envData.door); //开关范围为0 - 1
    initRandomBuf<quint8>(0,1,souceData->envData.water); //开关范围为0 - 1
    initRandomBuf<quint8>(0,1,souceData->envData.smoke); //开关范围为0 - 1

    souceData->envData.len = 4;

    //为设备信息初始化数据
    //    souceData->mDevInfo.mDevType.devName = "clever";
    char *buf = "clever";
    memcpy(souceData->mDevInfo.mDevType.devName,buf,strlen(buf));
    //    qDebug()<<"souceData->mDevInfo.mDevType.devName:" << souceData->mDevInfo.mDevType.devName;



    //其他数据特别初始化
//    initRandomBuf<quint8>(1,2,souceData->loopData.switchStatus);



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
//        *(buf+i) = baseNum + Random(socpe);//获取一个在1到5（即1+4）之间的随机数

        buf[i] = baseNum + Random(socpe);
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
    initRandomBuf<quint8>(1,2,data.switchStatus); //开关范围为0 - 1
//    for(int i = 0 ; i < 6 ;i++)
//    qDebug() << "initRandomBuf:" <<i<<*(data.sw+i);

    initRandomBuf<quint16>(500,500,data.cDrined);
    initRandomBuf<quint16>(10,20,data.voltagefrequency);
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
    data.num = 6;
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

    //为环境数据分配空间
    initUnitSpace(souceData->envData.tem);
    initUnitSpace(souceData->envData.hum);
    souceData->envData.door = new quint8[32];
    souceData->envData.water = new quint8[32];
    souceData->envData.smoke = new quint8[32];

    //为设备信息分配空间
    souceData->mDevInfo.mDevType.devName = new char[32];


}

/**
 * @brief num:第几相或第几个回路。。。 data:数据修改后的值 len：传入长度，四字节则不修改临界值
 * @param num
 * @param data
 */
void DataSouce::setData(unit *mUnit, int num, quint8 *data )
{
    for(int i =0 ; i< 16; i++)
        qDebug()<<"i:"<<*(data+i);

    int offset = 0;
    *(mUnit->minValue + num -1) =( *(data + offset++) << 8) +*(data + offset++);
    *(mUnit->maxValue + num -1) = (*(data + offset++) << 8 )+*(data + offset++);
    *(mUnit->cirMinValue + num -1) =( *(data + offset++) << 8) +*(data + offset++);
    *(mUnit->cirMaxValue + num -1) = (*(data + offset++) << 8 )+*(data + offset++);

    qDebug()<<"min:"<<*(mUnit->minValue + num -1);
    qDebug()<<"max:"<<*(mUnit->maxValue + num -1);
    qDebug()<<"cirmin:"<<*(mUnit->cirMinValue + num -1);
    qDebug()<<"cirmax:"<<*(mUnit->cirMaxValue + num -1);
}


void DataSouce::renewalSouceData()
{
    renewalUnit(souceData->inputPhrase.cur);
    renewalUnit(souceData->inputPhrase.vol);
    renewalUnit(souceData->loopData.cur);
    renewalUnit(souceData->loopData.vol);
    renewalUnit(souceData->outData.cur);
    renewalUnit(souceData->outData.vol);
}

void DataSouce::renewalUnit(unit &mUnit)
{
    initRandomBuf<quint16>(10,15,mUnit.currentValue);
}

/**
 * @brief 改变设备配置
 */
void DataSouce::changeDevSettings()
{
    devSetings *settings = get_devsetings();

    souceData->inputPhrase.len = settings->devPhaseNum;
    souceData->envData.len = settings->devSensorNum;
    souceData->loopData.cur.num = settings->devLoopNum; //
    souceData->outData.len = settings->devOutNum;

    memcpy(souceData->mDevInfo.mDevType.devName,settings->devName.toLatin1().data(),20);

    *(souceData->envData.door) = settings->entranceGuard1;
    *(souceData->envData.door + 1) = settings->entranceGuard2;
    *(souceData->envData.smoke) = settings->smoke;
    *(souceData->envData.water) = settings->water;


}










