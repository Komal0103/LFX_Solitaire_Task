#include "foundation.h"
#include <QMimeData>
#include <QString>
#include <QDebug>

Foundation::Foundation(int height, int width, QGraphicsItem *parent) : card(parent)
{
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    dropped_cards = 0;
    card_height = height;
    card_width = width;
}

bool Foundation::isFull()
{
    if (dropped_cards == 13)
        return true;
    return false;
}

void Foundation::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << event->mimeData()->imageData();
    int incoming_index = event->mimeData()->text().toInt();
    qDebug() << incoming_index;
    if (dropped_cards == 0) {
        if (incoming_index % 13 == 0) {
            event->setAccepted(true);
            dropped_cards++;
            revealed = incoming_index;
            top_card = new card(this);
            top_card->setIndex(incoming_index);
            top_card->setZvalue(dropped_cards);
            QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
            QPixmap scaled_pixmap = pixmap.scaled(card_width, card_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            top_card->setPixmapFromImage(scaled_pixmap);
        }
        else
            return;
    }
    else {
        if (event->mimeData()->hasImage() && event->mimeData()->hasText()) {
            if (incoming_index - revealed == 1){
                event->setAccepted(true);
                dropped_cards++;
                revealed = incoming_index;
                top_card = new card(this);
                top_card->setIndex(incoming_index);
                top_card->setZvalue(dropped_cards);
                QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
                QPixmap scaled_pixmap = pixmap.scaled(card_width, card_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                top_card->setPixmapFromImage(scaled_pixmap);
            }
        }
    }
}

void Foundation::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    card::dragEnterEvent(event);
}

