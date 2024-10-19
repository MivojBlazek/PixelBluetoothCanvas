#include "bluetoothselectwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BluetoothSelectWindow w;
    w.setWindowTitle("PixelBluetoothCanvas");
    w.show();
    return a.exec();
}
