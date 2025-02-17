#ifndef CARDTEST_H
#define CARDTEST_H

#include <QWidget>
#include "card.h"

namespace Ui {
class CardTest;
}

class CardTest : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit CardTest(QGraphicsItem *parent = nullptr);
    ~CardTest();
    void setCardParams();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Ui::CardTest *ui;
    card* card_;
};

#endif // CARDTEST_H
