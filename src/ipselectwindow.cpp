#include "ipselectwindow.h"
#include "ui_ipselectwindow.h"
#include "mainwindow.h"

IPSelectWindow::IPSelectWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IPSelectWindow)
{
    ui->setupUi(this);

    connect(ui->ConnectButton, &QPushButton::clicked, this, &IPSelectWindow::onConnectButtonClicked);
    connect(ui->IPLineEdit, &QLineEdit::returnPressed, ui->ConnectButton, &QPushButton::click);
}

IPSelectWindow::~IPSelectWindow()
{
    delete ui;
}

void IPSelectWindow::onConnectButtonClicked()
{
    this->hide();

    QString ipAddress = ui->IPLineEdit->text();
    MainWindow *mainWindow = new MainWindow(ipAddress);
    mainWindow->show();
}
