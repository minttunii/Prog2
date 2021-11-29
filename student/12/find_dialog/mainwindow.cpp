#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::onFindClicked);
    connect(ui->matchCheckBox, &QCheckBox::stateChanged, this, &MainWindow::onFindClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFindClicked()
{
    std::string filename = ui->fileLineEdit->text().toStdString();
    std::fstream filein(filename);

    if(!filein){
        ui->textBrowser->setText("File not found");
        return;
    }
    else{
        std::string wanted_word = ui->keyLineEdit->text().toStdString();
        std::string read_line = "";
        if(wanted_word == ""){
            ui->textBrowser->setText("File found");
            return;
        }
        while(getline(filein, read_line)){

            if(read_line.find(wanted_word) != std::string::npos){
                ui->textBrowser->setText("Word found");
                filein.close();
                return;
            }
        }
        ui->textBrowser->setText("Word not found");
    }
}


