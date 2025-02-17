#include "cardtest.h"
#include <QDebug>

CardTest::CardTest(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    card_ = new card();
    setCardParams();
    // setMinimumSize(200, 200);
}

CardTest::~CardTest()
{
}

void CardTest::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "CardTest painter here!";
    painter->translate(25, 25);
    card_->paint(painter, nullptr, nullptr);
}

void CardTest::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    card_->dragEnterEvent(event);
}

void CardTest::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    card_->dropEvent(event);
}

void CardTest::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    card_->mousePressEvent(event);
}

void CardTest::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    card_->mouseReleaseEvent(event);
}

void CardTest::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    card_->mouseMoveEvent(event);
}

void CardTest::setCardParams() {
    card_->setIndex(52);
    card_->setPath(":/img/images/JOKER.png");
    card_->setPixmapImage(":/img/images/JOKER.png");
    card_->setZvalue(1);
}

QRectF CardTest::boundingRect() const
{
    return card_->boundingRect();
}
