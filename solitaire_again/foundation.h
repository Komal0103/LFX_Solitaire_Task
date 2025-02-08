#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <QGraphicsItem>
#include <QApplication>
#include <QBitmap>
#include <QCursor>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QParallelAnimationGroup;
QT_END_NAMESPACE

class Foundation : public QGraphicsObject
{
    Q_OBJECT
public:
    Foundation(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    int cards_dropped = 0;
    int top = 0;
    bool dragOver = false;
};

#endif // FOUNDATION_H
