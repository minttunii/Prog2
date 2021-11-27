#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <iostream>

int TimerIntervalMs = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onSecTimer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartButtonClicked()
{
    timer->start(TimerIntervalMs);
}

void MainWindow::onStopButtonClicked()
{
    timer->stop();
}

void MainWindow::onResetButtonClicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

}

void MainWindow::onCloseButtonClicked()
{
    close();
}

void MainWindow::onSecTimer()
{
    int seconds = ui->lcdNumberSec->intValue();
    int minutes = ui->lcdNumberMin->intValue();

    ++seconds;
    if(seconds == 60){
        seconds = 0;
        ++minutes;
    }
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);

    static int i = 0;
    ++i;
    std::cout << i << std::endl;
}
