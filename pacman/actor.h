#ifndef ACTOR_H
#define ACTOR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>


class Actor : public QObject,public QGraphicsPixmapItem
{
public:
    Actor(QGraphicsItem * parent = 0);
public slots:
    void move();
};

#endif // ACTOR_H
