#include "config.h"

#include "scene.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColorDialog>
#include <QPainter>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent},
    color(Qt::white)
{

}

void Scene::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, qobject_cast<QWidget *>(this->parent()));
    if (newColor.isValid())
    {
        color = newColor;
    }
    emit colorChanged();
}

QColor Scene::getColor()
{
    return color;
}

void Scene::clearScene()
{
    this->clear();
}

QImage Scene::getImage()
{
    QImage image(DISPLAY_WIDTH * PIXEL_SIZE, DISPLAY_HEIGHT * PIXEL_SIZE, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    this->render(&painter, image.rect(), QRectF(0, 0, DISPLAY_WIDTH * PIXEL_SIZE, DISPLAY_HEIGHT * PIXEL_SIZE));
    QImage scaledImage = image.scaled(128, 128, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
    return scaledImage;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = true;
        lastPoint = event->scenePos();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawing)
    {
        QPen pen(color, PIXEL_SIZE);
        QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(lastPoint, event->scenePos()));
        line->setPen(pen);
        addItem(line);

        lastPoint = event->scenePos();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = false;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
