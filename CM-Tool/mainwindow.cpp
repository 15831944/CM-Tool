#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "udp/datasent.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    HeartBeat *heartt = new HeartBeat(this,18725);
    //    souce = new DataSouce;  //更新数据
    //    parameterData *data = souce->getSouceData();  //获取数据



    //    souceData_To_protcldata();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutdone()));
    timer->start(1*1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //    qDebug()<<"IP:"<<heart->getAddr().toString()<<"端口："<<heart->getPort()<<"数据:"<<heart->getData();
    //    heart->sendData(); //向指定端口发送数据
    //    qDebug()<<"数据"<<souce->getSouceData()->inputPhrase.cur.currentValue;

    souceData_To_protcldata();
}

void MainWindow::timeoutdone()
{
    souceData_To_protcldata();
}
