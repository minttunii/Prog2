#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::onCountButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::count_bmi(double &weight, double &height)
{
    return weight / (height/100 * height/100) ;
}

void MainWindow::bmi_info(double &bmi)
{
    if(bmi < 18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if(bmi > 25){
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else{
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

void MainWindow::onCountButtonClicked()
{
    double height = ui->heightLineEdit->text().toDouble();
    double weight = ui->weightLineEdit->text().toDouble();

    if(height == 0 || ui->heightLabel->text() == ""){
        ui->resultLabel->setText("Cannot count");
        return;
    }

    double bmi = count_bmi(weight, height);
    ui->resultLabel->setText(QString::number(bmi));

    bmi_info(bmi);
}

