﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include "udp/datasent.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void timeoutdone();

private:
    Ui::MainWindow *ui;


protected:
//     HeartBeat *heart ;
//     DataSouce *souce;
};

#endif // MAINWINDOW_H
