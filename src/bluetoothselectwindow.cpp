#include "bluetoothselectwindow.h"
#include "ui_bluetoothselectwindow.h"
#include "mainwindow.h"
#include <QBluetoothLocalDevice>
#include <QDebug>

BluetoothSelectWindow::BluetoothSelectWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::BluetoothSelectWindow)
{
    ui->setupUi(this);

    QBluetoothLocalDevice localDevice;
    pairedDevices = localDevice.connectedDevices();

    setStyleSheet("background-color: #2A2A2A;");
    ui->ConnectButton->setStyleSheet("QPushButton { color: white; background-color: #2A2A2A; }"
                                     "QPushButton:hover { background-color: #4A4A4A; }"
                                     "QPushButton:pressed { background-color: #3A3A3A; }");
    ui->BluetoothLineEdit->setStyleSheet("color: white;");

    connect(ui->ConnectButton, &QPushButton::clicked, this, &BluetoothSelectWindow::onConnectButtonClicked);
    connect(ui->BluetoothLineEdit, &QLineEdit::returnPressed, ui->ConnectButton, &QPushButton::click);
    connect(ui->BluetoothLineEdit, &QLineEdit::textEdited, this, &BluetoothSelectWindow::clearErrorMessage);
}

BluetoothSelectWindow::~BluetoothSelectWindow()
{
    delete ui;
}

void BluetoothSelectWindow::onConnectButtonClicked()
{

    QString bluetoothAddress = ui->BluetoothLineEdit->text();
    for (QBluetoothAddress &deviceAddress : pairedDevices)
    {
        if (bluetoothAddress == deviceAddress.toString())
        {
            this->hide();
            MainWindow *mainWindow = new MainWindow(bluetoothAddress);
            mainWindow->show();
            return;
        }
    }
    ui->ErrorLabel->setText("Error: No device found.");
}

void BluetoothSelectWindow::clearErrorMessage()
{
    ui->ErrorLabel->clear();
}
