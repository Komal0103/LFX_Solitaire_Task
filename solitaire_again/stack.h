#ifndef STACK_H
#define STACK_H

#include "card.h"
#include <QGraphicsItem>
#include <QObject>

class Stack : public card
{
    Q_OBJECT
public:
    Stack(QVector<int> assigned_cards, QGraphicsItem *parent = nullptr); // assign cards here only
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void flip_stack();
    void switch_to_next_card();
    int get_num_cards();

protected:
    // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    card* top_card;
    QVector<int> card_indices;
    int revealed_card;
    int on_card;
    int num_cards; // cards left in the stack
    bool isEmpty = false;
};

#endif // STACK_H
