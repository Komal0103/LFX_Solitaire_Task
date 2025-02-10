#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "card.h"

class Foundation : public card
{
public:
    Foundation(int height, int width, QGraphicsItem *parent = nullptr);
    bool isFull();

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    int dropped_cards;
    int revealed;
    card* top_card;
    int card_height;
    int card_width;
};

#endif // FOUNDATION_H
