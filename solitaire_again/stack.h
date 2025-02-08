#ifndef STACK_H
#define STACK_H

#include "card.h"
#include <QGraphicsItem>

class Stack : public QGraphicsItem
{
    Q_OBJECT
public:
    QVector<int> assigned_cards; // assign cards here only
    // QRectF boundingRect() const override;
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void switch_to_next_card ();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<int> card_indices;
    int revealed_card;
    int num_cards; // cards left in the stack
    bool isEmpty = false;
};

#endif // STACK_H
