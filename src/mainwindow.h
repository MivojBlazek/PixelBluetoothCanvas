#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &ipAddress, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString ipAddress;
    Scene *initScene();
    void updateLabel();
    void sendText();
    void sendImage();
    QByteArray convertImageToRGB565(const QImage &image);
};
#endif // MAINWINDOW_H
