#include "foundation.h"

Foundation::Foundation(QGraphicsItem *parent) : QGraphicsObject(parent) {
    if (dropped_cards == 13)
        setAcceptDrops(false);
    else
        setAcceptDrops(true);

}
