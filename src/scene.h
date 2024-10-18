#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPointF>
#include <QColor>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void changeColor();
    QColor getColor();
    void clearScene();
    QImage getImage();

signals:
    void colorChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor color;
    bool drawing;
    QPointF lastPoint;
};

#endif // SCENE_H
