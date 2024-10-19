#ifndef BLUETOOTHDATASENDER_H
#define BLUETOOTHDATASENDER_H

#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QObject>

class BluetoothDataSender : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothDataSender(QObject *parent = nullptr);
    void connectToDevice(const QString &address, const QBluetoothUuid &uuid);
    void sendData(const QByteArray &data);

private:
    QBluetoothSocket *socket;
};

#endif // BLUETOOTHDATASENDER_H
