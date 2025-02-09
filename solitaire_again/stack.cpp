#include "stack.h"

#include <QApplication>
#include <QBitmap>
#include <QCursor>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QRandomGenerator>
#include <QWidget>
#include <QDebug>

Stack::Stack(QVector<int> assigned_cards, QGraphicsItem* parent) : card_indices(assigned_cards), card(parent)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptDrops(false);
    num_cards = assigned_cards.length();
    on_card = num_cards - 1;
    revealed_card = assigned_cards[num_cards - 1];
    QString img_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
    top_card = new card(this);
    top_card->setPath(img_path);
    top_card->setPixmapImage(img_path);
    top_card->setZvalue(num_cards);
    top_card->setIndex(revealed_card);
}

QRectF Stack::boundingRect() const
{
    return card::boundingRect();
}

void Stack::switch_to_next_card()
{
    on_card--;
    qDebug() << on_card;
    if (on_card >= 0){
        revealed_card = card_indices[on_card];
        QString img_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
        top_card = new card(this);
        top_card->setPath(img_path);
        top_card->setPixmapImage(img_path);
        top_card->setZvalue(num_cards);
        top_card->setIndex(revealed_card);
        qDebug() << "switched!";
    }
    else {
        flip_stack();
    }
}

int Stack::get_num_cards()
{
    return num_cards;
}

void Stack::flip_stack() {
    on_card = num_cards - 1;
    revealed_card = card_indices[on_card];
    QString img_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
    top_card = new card(this);
    top_card->setPixmapImage(img_path);
    top_card->setZvalue(num_cards);
    top_card->setIndex(revealed_card);
}

void Stack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QString image_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
    const QPixmap pixmap(image_path);
    painter->drawPixmap(boundingRect().toRect(), pixmap);
}

// void Stack::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
//     setCursor(Qt::ClosedHandCursor);
// }

void Stack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    mime->setImageData(QImage(top_card->getPixmapImage()));
    QPixmap pixmap_(top_card->getPixmapImage());
    QPainter painter(&pixmap_);
    painter.translate(15, 15);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, nullptr, nullptr);
    painter.end();

    pixmap_.setMask(pixmap_.createHeuristicMask());
    drag->setPixmap(pixmap_);
    drag->setHotSpot(QPoint(pixmap_.width()/2, pixmap_.height()/2));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
    num_cards--;
    on_card--;
    card_indices.pop_back();
    if (num_cards == 0){
        isEmpty = true;
        flip_stack();
    }
    else {
        revealed_card = card_indices[num_cards - 1];
        delete top_card;
        top_card = nullptr;
        QString img_path = IMAGE_PATH_PREFIX + QString::number(revealed_card) + IMAGE_EXT;
        top_card = new card(this);
        top_card->setPath(img_path);
        top_card->setPixmapImage(img_path);
        top_card->setZvalue(num_cards);
        top_card->setIndex(revealed_card);
    }
}

// void Stack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// {
//     setCursor(Qt::OpenHandCursor);
// }
