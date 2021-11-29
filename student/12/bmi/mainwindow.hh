#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <iostream>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double count_bmi(double& weight, double& height);
    void bmi_info(double& bmi);

private slots:
    void onCountButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
