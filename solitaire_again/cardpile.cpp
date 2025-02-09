#include "cardpile.h"

#include <QString>

CardPile::CardPile(QVector<int> card_indices, QWidget *parent)
    : QGraphicsScene(parent)
{
    // ui->setupUi(this);
    for (QVector<int>::iterator i=card_indices.begin(); i<card_indices.end(); ++i) {
        QString path = IMAGE_PATH_PREFIX + QString::number(*i) + IMAGE_EXT;
        // card new_card(path, 1, (0, 0));
    }
}

CardPile::~CardPile()
{
}
