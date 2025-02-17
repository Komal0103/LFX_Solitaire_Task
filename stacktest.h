#ifndef STACKTEST_H
#define STACKTEST_H

#include "stack.h"
#include <QWidget>
#include <QGraphicsItem>

class StackTest : public QGraphicsObject
{
    Q_OBJECT
public:
    StackTest(QGraphicsItem *parent = nullptr);
    // void test_flip_stack();
    void test_switch_to_next_card();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // int test_get_num_cards();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QVector<int> assigned{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Stack *stack_ = new Stack(assigned);
};

#endif // STACKTEST_H
