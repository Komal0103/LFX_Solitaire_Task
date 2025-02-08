#ifndef CARDPILE_H
#define CARDPILE_H

#include <QWidget>
#include "card.h"

namespace Ui {
class CardPile;
}

class CardPile : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CardPile(QVector<int> card_indices, QWidget *parent = nullptr);
    ~CardPile();
    int get_number_of_cards();
    int get_revealed_card();
    void flip_next_card();

private:
    Ui::CardPile *ui;
    QList<card *> cards_in_pile;
    int num_cards;
    int revealed_card; // index of revealed card
};

#endif // CARDPILE_H
