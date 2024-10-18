#include "config.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QIcon>

MainWindow::MainWindow(const QString &ipAddress, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    ipAddress(ipAddress)
{
    ui->setupUi(this);

    setWindowTitle("PixelNetCanvas");
    setStyleSheet("background-color: #2A2A2A;");

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
    //TODO
}

void MainWindow::sendImage()
{
    Scene *scene = dynamic_cast<Scene *>(ui->graphicsView->scene());
    if (scene)
    {
        QImage image = scene->getImage();
        QByteArray imageData = convertImageToRGB565(image);
        //TODO
    }
}

QByteArray MainWindow::convertImageToRGB565(const QImage &image)
{
    //TODO
    QByteArray byteArray;
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            QColor color = image.pixelColor(x, y);
            quint16 rgb565Pixel = ((color.red() >> 3) << 11) | ((color.green() >> 2) << 5) | (color.blue() >> 3);
            byteArray.append(reinterpret_cast<const char*>(&rgb565Pixel), 2);
        }
    }
    return byteArray;
}
