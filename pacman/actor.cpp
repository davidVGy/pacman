#include "actor.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

Actor::Actor(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    int random_number = rand() % 700;
    setPos(random_number,0);
    // drew the rect
    setPixmap(QPixmap(":/images/img/pacman_sheet.png"));
//    setTransformOriginPoint(50,50);
//    setRotation(180);

}
