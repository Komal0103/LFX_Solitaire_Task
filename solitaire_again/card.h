#ifndef CARD_H
#define CARD_H

#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QGraphicsPixmapItem>

namespace Ui {
class QDragEnterEvent;
class QDropEvent;
class card;
}

class card : public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit card(QWidget *parent = nullptr);
    ~card();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::card *ui;
};

#endif // CARD_H
