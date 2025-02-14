#ifndef CARDTEST_H
#define CARDTEST_H

#include <QWidget>
#include "card.h"

namespace Ui {
class CardTest;
}

class CardTest : public QWidget
{
    Q_OBJECT

public:
    explicit CardTest(QWidget *parent = nullptr);
    ~CardTest();
    void setCardParams();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::CardTest *ui;
    card* card_ = new card();
};

#endif // CARDTEST_H
