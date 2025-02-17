#include "stacktest.h"
#include <QDebug>
#include <QKeyEvent>

StackTest::StackTest(QGraphicsItem* parent) : QGraphicsObject(parent) {
    // setMinimumSize(200, 300);
    setAcceptedMouseButtons(Qt::LeftButton);
    stack_ = new Stack(assigned);
}

void StackTest::test_switch_to_next_card()
{
    stack_->switch_to_next_card();
}

QRectF StackTest::boundingRect() const
{
    return QRectF(0, 0, 400, 400);
}

void StackTest::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    stack_->mouseMoveEvent(event);
}

void StackTest::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // painter->translate(25, 25);
    stack_->paint(painter, nullptr, nullptr);
}

void StackTest::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        event->setAccepted(true);
        qDebug() << "Switched to next card!";
        test_switch_to_next_card();
    }
    else {
        // do nothing
        event->setAccepted(false);
    }
}
