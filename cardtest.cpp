#include "cardtest.h"
#include "ui_cardtest.h"

CardTest::CardTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardTest)
{
    ui->setupUi(this);
    setMinimumSize(200, 200);
}

CardTest::~CardTest()
{
    delete ui;
}

void CardTest::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(25, 25);
    card_->paint(&painter, nullptr, nullptr);
}

void CardTest::setCardParams() {
    card_->setIndex(52);
    card_->setPath(":/img/images/JOKER.png");
    card_->setPixmapImage(":/img/images/JOKER.png");
    card_->setZvalue(1);
}
