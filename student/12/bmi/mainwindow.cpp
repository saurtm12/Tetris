#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "utilis.hh"
#include <cmath>
const std::string LOW = "You are underweight.",
                  NORM = "Your weight is normal.",
                  HIGH = "You are overweight.";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::pushCount);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::pushCount()
{
    std::string height = ui->heightLineEdit->text().toStdString();
    std::string weight = ui->weightLineEdit->text().toStdString();
    /*
    if (utils::is_numeric(height,false))
        return;
    if (utils::is_numeric(weight,false))
        return;
    */
    double h = std::stod(height);
    double w = std::stod(weight);

    double bmi = w/pow(h/100,2);
    auto result = std::to_string(bmi);
    QString result_(result.c_str());
    ui->resultLabel->setText(result_);
    if (bmi < 18.5)
    {
        QString LOW_(LOW.c_str());
        ui->infoTextBrowser->setText(LOW_);
    }
    if (bmi >= 25)
    {
        QString HIGH_(HIGH.c_str());
        ui->infoTextBrowser->setText(HIGH_);
    }
    QString NORM_(NORM.c_str());
    ui->infoTextBrowser->setText(NORM_);
}

