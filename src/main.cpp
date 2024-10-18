#include "ipselectwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPSelectWindow w;
    w.setWindowTitle("PixelNetCanvas");
    w.show();
    return a.exec();
}
