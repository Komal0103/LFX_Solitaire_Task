#ifndef CARD_H
#define CARD_H

#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QGraphicsPixmapItem>

#define IMAGE_PATH_PREFIX ":/img/"
#define IMAGE_EXT ".png"
#define DECK_SIZE 52
#define SUITS 4
#define CARDS_PER_SUIT 13
#define PILES 7
#define STOCK_SIZE 24

static constexpr int MAX_PILE_SIZE = CARDS_PER_SUIT + PILES;

namespace Ui {
class QDragEnterEvent;
class QDropEvent;
class card;
}

class card : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit card(const QString &path, int z, QPointF position);
    ~card();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void flipCard();
    card* custom_childAt(QPointF position);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap pixmap;
    int index;
    int z;
    bool revealed = false;
    QString &path;
    bool isFlipped = false;
};

#endif // CARD_H
