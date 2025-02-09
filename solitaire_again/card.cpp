#include "card.h"
#include <QMimeData>
#include <QDrag>
#include <QApplication>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QBitmap>

card::card(QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    setAcceptDrops(false);
    // setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

card::~card() {}

QRectF card::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->scale(0.5, 0.5);
    painter->drawPixmap(QPointF(0, 0), pixmap);
}

void card::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage() && card_correct(event->mimeData()->text())) {
        event->setAccepted(true);
        // change the z value also somehow
        update();
    }
    else {
        event->setAccepted(false);
    }
}

// basic implement only created. I suppose the same implementation can be used for the Foundation class event
void card::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->setAccepted(true);
        pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        update();
    }
    else {
        event->setAccepted(false);
    }
}

void card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}

void card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
}

void card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    mime->setImageData(QImage(path_));
    QPainter painter(&pixmap);
    painter.translate(20, 20);
    painter.setRenderHint(QPainter::Antialiasing);
    // paint(&painter, nullptr, nullptr);
    painter.end();

    pixmap.setMask(pixmap.createHeuristicMask());
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

bool card::card_correct (QString ind) {
    bool done;
    int ind_ = ind.toInt(&done);
    qDebug() << ind_;
    qDebug() << index_;
    if (done) {
        if ((ind_ - index_) % 13 == 1 || (ind_ - index_) % 13 == -1)
            return true;
        else
            return false;
    }
    return false;
}

void card::setPath(QString path)
{
    path_ = path;
}

void card::setPixmapImage(QString path)
{
    QPixmap dpixmap = QPixmap(path);
    pixmap = dpixmap.scaled(300, 350, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qDebug() << pixmap.width();
    qDebug() << pixmap.height();
}

void card::setZvalue(int z)
{
    setZValue(z);
}

void card::setIndex(int ind)
{
    index_ = ind;
}

QString card::getPixmapImage()
{
    return path_;
}

int card::getIndex()
{
    return index_;
}
