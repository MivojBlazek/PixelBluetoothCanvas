#include "config.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "bluetoothdatasender.h"
#include <QIcon>
#include <QBluetoothUuid>
#include <QDebug>
#include <QTimer>
#include <QProgressBar>

MainWindow::MainWindow(const QString &bluetoothAddress, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    bluetoothAddress(bluetoothAddress)
{
    ui->setupUi(this);

    setWindowTitle("PixelBluetoothCanvas");

    Scene *scene = initScene();

    QGraphicsView *view = ui->graphicsView;
    view->setStyleSheet("background-color: #000000; border: 1px solid #FFFFFF;");

    view->setScene(scene);
    view->setFocusPolicy(Qt::StrongFocus);

    ui->ColorButton->setIcon(QIcon(":/icons/color_icon.png"));
    ui->ColorButton->setToolTip("Select color");
    ui->ColorLabel->setStyleSheet(QString("background-color: " + scene->getColor().name() + ";"));

    connect(scene, &Scene::colorChanged, this, &MainWindow::updateLabel);

    connect(ui->ColorButton, &QPushButton::clicked, scene, &Scene::changeColor);
    connect(ui->ClearButton, &QPushButton::clicked, scene, &Scene::clearScene);


    connect(ui->SendTextButton, &QPushButton::clicked, this, &MainWindow::sendText);
    connect(ui->SendImageButton, &QPushButton::clicked, this, &MainWindow::sendImage);

    bluetoothSender.connectToDevice(bluetoothAddress, QBluetoothUuid(QBluetoothUuid::ServiceClassUuid::SerialPort));

    progressBar = new QProgressBar(this);
    ui->ProgressBarLayout->addWidget(progressBar);
    progressBar->setRange(0, 100);
    progressBar->setVisible(false);

    connect(ui->SendTextLineEdit, &QLineEdit::returnPressed, ui->SendTextButton, &QPushButton::click);

    setStyleSheet("background-color: #2A2A2A;");
    ui->SendTextButton->setStyleSheet("QPushButton { color: white; background-color: #2A2A2A; }"
                                     "QPushButton:hover { background-color: #4A4A4A; }"
                                     "QPushButton:pressed { background-color: #3A3A3A; }");
    ui->SendImageButton->setStyleSheet("QPushButton { color: white; background-color: #2A2A2A; }"
                                      "QPushButton:hover { background-color: #4A4A4A; }"
                                      "QPushButton:pressed { background-color: #3A3A3A; }");
    ui->ClearButton->setStyleSheet("QPushButton { color: white; background-color: #2A2A2A; }"
                                       "QPushButton:hover { background-color: #4A4A4A; }"
                                       "QPushButton:pressed { background-color: #3A3A3A; }");
    ui->SendTextLineEdit->setStyleSheet("color: white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Scene *MainWindow::initScene()
{
    Scene *scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setSceneRect(0, 0, PIXEL_SIZE * DISPLAY_WIDTH, PIXEL_SIZE * DISPLAY_HEIGHT);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    return scene;
}

void MainWindow::updateLabel()
{
    Scene *scene = dynamic_cast<Scene *>(ui->graphicsView->scene());
    if (scene)
    {
        ui->ColorLabel->setStyleSheet(QString("background-color: " + scene->getColor().name() + ";"));
    }
}

void MainWindow::sendText()
{
    QString textToSend = ui->SendTextLineEdit->text();
    QByteArray textData = textToSend.toUtf8();
    textData.prepend(static_cast<char>(0x02));
    bluetoothSender.sendData(textData);
}

void MainWindow::sendImage()
{
    Scene *scene = dynamic_cast<Scene *>(ui->graphicsView->scene());
    if (scene)
    {
        QImage image = scene->getImage();
        imageData = convertImageToRGB565(image);

        // Send data in smaller chunks to let device process it
        bytesSent = 0;
        firstChunk = true;

        ui->SendTextButton->setEnabled(false);
        ui->SendImageButton->setEnabled(false);

        progressBar->setVisible(true);
        progressBar->setValue(0);

        sendTimer = new QTimer(this);
        connect(sendTimer, &QTimer::timeout, this, &MainWindow::sendNextChunk);
        sendTimer->start(70);
    }
}

QByteArray MainWindow::convertImageToRGB565(const QImage &image)
{
    QByteArray byteArray;
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            QColor color = image.pixelColor(x, y);
            quint16 rgb565Pixel = ((color.red() >> 3) << 11) | ((color.green() >> 2) << 5) | (color.blue() >> 3);
            byteArray.append(static_cast<char>(rgb565Pixel & 0xFF));
            byteArray.append(static_cast<char>((rgb565Pixel >> 8) & 0xFF));
        }
    }
    return byteArray;
}

void MainWindow::sendNextChunk()
{
    if (bytesSent < imageData.size())
    {
        int bytesToSend = qMin(chunkSize, imageData.size() - bytesSent);

        QByteArray chunk = imageData.mid(bytesSent, chunkSize);
        if (firstChunk)
        {
            chunk.prepend(static_cast<char>(0x00));
            firstChunk = false;
        }
        else
        {
            chunk.prepend(static_cast<char>(0x01));
        }
        bluetoothSender.sendData(chunk);

        bytesSent += bytesToSend;

        int progress = static_cast<int>((static_cast<float>(bytesSent) / imageData.size()) * 100);
        progressBar->setValue(progress);
    }
    else
    {
        // Image sent
        sendTimer->stop();

        ui->SendTextButton->setEnabled(true);
        ui->SendImageButton->setEnabled(true);

        progressBar->setVisible(false);
    }
}
