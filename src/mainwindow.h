#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"

#include "scene.h"
#include "bluetoothdatasender.h"
#include <QMainWindow>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &bluetoothAddress, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString bluetoothAddress;
    BluetoothDataSender bluetoothSender;

    QProgressBar *progressBar;
    QByteArray imageData;
    const int chunkSize = CHUNK_SIZE;
    int bytesSent;
    QTimer *sendTimer;
    bool firstChunk;

    Scene *initScene();
    void updateLabel();
    void sendText();
    void sendImage();
    QByteArray convertImageToRGB565(const QImage &image);
    void sendNextChunk();
};
#endif // MAINWINDOW_H
