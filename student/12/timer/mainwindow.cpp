#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    minute = 0;
    second = 0;
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::click_close_button);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::click_reset_button);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::click_stop_button);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::click_start_button);
    connect(timer, &QTimer::timeout, this, &MainWindow::finish_1000ms);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::click_close_button()
{
    this->close();
}
void MainWindow::click_reset_button()
{
    timer->stop();
    minute = 0;
    second = 0;
    ui->lcdNumberMin->display(minute);
    ui->lcdNumberSec->display(second);
}
void MainWindow::click_stop_button()
{
    remain = timer->remainingTime();
    timer->stop();
}
void MainWindow::click_start_button()
{
    timer->start(remain);
}
void MainWindow::finish_1000ms()
{
    timer->start(1000);
    second++;
    if (second == 60)
    {
        second =0;
        minute++;
    }
    ui->lcdNumberMin->display(minute);
    ui->lcdNumberSec->display(second);
}
