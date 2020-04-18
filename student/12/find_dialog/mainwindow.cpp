#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "read_file.hh"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::findButton_pressed);
    connect(ui->closePushButton, &QPushButton::clicked,this, &MainWindow::closeButton_pressed);
    connect(ui->matchCheckBox, &QCheckBox::stateChanged,this, &MainWindow::change_state);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_state()
{
    tick = ui->matchCheckBox->isChecked();
}

void MainWindow::findButton_pressed()
{
    std::string file = ui->fileLineEdit->text().toStdString();
    std::string text = ui->keyLineEdit->text().toStdString();
    bool tick = ui->matchCheckBox->checkState();
    std::string result = findWord(file,text,tick);
    ui->textBrowser->reload();
    if (result == FNOT_FOUND)
    {
        QString fnot_found(FNOT_FOUND.c_str());

        ui->textBrowser->setText(fnot_found);
        return;
    }
    if (text == EMPTY)
    {
        QString f_found(F_FOUND.c_str());
        ui->textBrowser->setText(f_found);
        return;
    }
    if (result == W_FOUND)
    {
        QString w_found(W_FOUND.c_str());
        ui->textBrowser->setText(w_found);
        return;
    }
    QString wnot_found(WNOT_FOUND.c_str());
    ui->textBrowser->setText(wnot_found);
    return;

}

void MainWindow::closeButton_pressed()
{
    this->close();
}
