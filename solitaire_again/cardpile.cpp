#include "cardpile.h"
#include "ui_cardpile.h"

CardPile::CardPile(QWidget *parent)
    : QGraphicsScene(parent)
    , ui(new Ui::CardPile)
{
    ui->setupUi(this);
}

CardPile::~CardPile()
{
    delete ui;
}
