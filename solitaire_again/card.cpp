#include "card.h"
#include "ui_card.h"

#include <QtWidgets>

card::card(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::card)
{
    // ui->setupUi(this);
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    QLabel *draggableIcon = new QLabel(this);
    draggableIcon->setPixmap(QPixmap(":/img/icon.png"));
    draggableIcon->move(10, 10);
    draggableIcon->show();
    draggableIcon->setAttribute(Qt::WA_DeleteOnClose);
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

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

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
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child) {
        return;
    }
    const QPixmap *pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << *pixmap <<QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    child->setParent(nullptr);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        delete child;
    }
    else {
        child->setParent(this);
        child->move(event->pos() - drag->hotSpot());
        child->show();
    }
}

card::~card()
{
    delete ui;
}
