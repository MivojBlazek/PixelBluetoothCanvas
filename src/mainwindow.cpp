#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(const QString &ipAddress, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    ipAddress(ipAddress)
{
    ui->setupUi(this);
    qDebug() << "IP Address received:" << ipAddress;
}

MainWindow::~MainWindow()
{
    delete ui;
}
