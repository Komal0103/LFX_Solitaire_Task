#include "card.h"

#include <QtWidgets>

card::card(const QString &path, int z, QPointF position)
{
    // ui->setupUi(this);
    setPixmap(QPixmap(path));
    setPos(position);
    setZValue(z);
    moveBy(10, 10);
    show();
    // setMinimumSize(200, 200);
    // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    // QLabel *draggableIcon = new QLabel(this);
    // draggableIcon->setPixmap(QPixmap(":/img/icon.png"));
    // draggableIcon->move(10, 10);
    // draggableIcon->show();
    // draggableIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void card::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void card::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void card::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        isFlipped = true;

        // QLabel *newIcon = new QLabel(this);
        // newIcon->setPixmap(pixmap);
        // newIcon->move(event->pos() - offset);
        // newIcon->show();
        // newIcon->setAttribute(Qt::WA_DeleteOnClose);

        card *dropped_card = new card(path, z, event->pos() - offset, this);
        dropped_card->show();

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void card::mousePressEvent(QMouseEvent *event) {
    card *child = custom_childAt(event->pos());
    if (!child) {
        return;
    }
    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << (event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    child->setParentItem(nullptr);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        delete child;
    }
    else {
        child->setParentItem(this);
        child->moveBy((event->pos() - drag->hotSpot()).x(), (event->pos() - drag->hotSpot()).y());
        child->show();
    }
}

card* card::custom_childAt(QPointF position) {
    const QList<QGraphicsItem*> list_children = this->childItems();
    card *found_child;
    for (QGraphicsItem* child : list_children) {
        if (child->contains(child->mapFromParent(position))) {
            found_child = static_cast<card*>(child);
        }
    }
    return nullptr;
}

QRectF card::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

card::~card()
{
}
