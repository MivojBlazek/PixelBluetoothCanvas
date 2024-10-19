#ifndef BLUETOOTHSELECTWINDOW_H
#define BLUETOOTHSELECTWINDOW_H

#include <QWidget>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>

namespace Ui {
class BluetoothSelectWindow;
}

class BluetoothSelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothSelectWindow(QWidget *parent = nullptr);
    ~BluetoothSelectWindow();

private:
    Ui::BluetoothSelectWindow *ui;

    QList<QBluetoothAddress> pairedDevices;
    void onConnectButtonClicked();
    void clearErrorMessage();
};

#endif // BLUETOOTHSELECTWINDOW_H