#include "bluetoothdatasender.h"

#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QBluetoothAddress>

BluetoothDataSender::BluetoothDataSender(QObject *parent)
    : QObject{parent}
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
}

void BluetoothDataSender::connectToDevice(const QString &address, const QBluetoothUuid &uuid)
{
    QBluetoothAddress bluetoothAddress(address);
    socket->connectToService(bluetoothAddress, uuid);
}

void BluetoothDataSender::sendData(const QByteArray &data)
{
    if (socket->state() == QBluetoothSocket::SocketState::ConnectedState)
    {
        socket->write(data);
    }
}
