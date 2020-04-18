#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::count)
}

MainWindow::~MainWindow()
{
    delete ui;
}
MainWindow::count()
{
    auto height = ui->heightLineEdit->text().toStdString();
    auto weight = ui->weightLineEdit->text().toStdString();

}

