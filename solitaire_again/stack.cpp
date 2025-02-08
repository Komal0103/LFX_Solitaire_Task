#include "stack.h"

#include <QApplication>
#include <QBitmap>
#include <QCursor>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QRandomGenerator>
#include <QWidget>

Stack::Stack(QVector<int> assigned_cards) : card_indices(assigned_cards)
{
    setCursor (Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    revealed_card = assigned_cards[num_cards];
}

QRectF Stack::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void Stack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QString image_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
    const QPixmap pixmap(image_path);
    painter->drawPixmap(boundingRect().toRect(), pixmap);
}

void Stack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void Stack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
        return;

    QDrag *dragObject = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    dragObject->setMimeData(mime);

    static int n = 0;
    if (n++ && QRandomGenerator::global()->bounded(3) == 0) {
        QImage image(":/img/JOKER.png");
        mime->setImageData(image);
        dragObject->setPixmap(QPixmap::fromImage(image).scaled(3., 40));
        dragObject->setHotSpot(QPoint(15, 30));
    }
    else {
        QString path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
        QImage img (path);
        mime->setImageData(img);
        QPixmap pixmap(34, 34);
        QPainter *painter =  new QPainter(&pixmap);
        painter->translate(15, 15);
        painter->setRenderHint(QPainter::Antialiasing); //  | QPainter::SmoothPixmapTransform
        paint(painter, nullptr, nullptr);
        painter->end();

        pixmap.setMask(pixmap.createHeuristicMask());

        dragObject->setPixmap(pixmap);
        dragObject->setHotSpot(QPoint(15, 20));

        num_cards--;
        revealed_card = card_indices[num_cards];
        paint(painter, nullptr, nullptr);
    }
    dragObject->exec();
    setCursor(Qt::OpenHandCursor);
}

void Stack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}
