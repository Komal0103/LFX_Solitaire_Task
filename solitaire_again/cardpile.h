#ifndef CARDPILE_H
#define CARDPILE_H

#include <QWidget>
#include "card.h"

namespace Ui {
class CardPile;
}

class CardPile : public QGraphicsScene, public card
{
    Q_OBJECT

public:
    explicit CardPile(QWidget *parent = nullptr);
    ~CardPile();

private:
    Ui::CardPile *ui;
};

#endif // CARDPILE_H
