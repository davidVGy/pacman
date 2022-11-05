#ifndef ACTOR_H
#define ACTOR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <arena.h>

class Actor : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    vector<vector<int>> map;
    Actor(Arena *mapGame, QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);
    enum stateKey {IDE, RIGHT, LEFT, UP, DOWN} keypress = IDE;

public slots:
    void move();

private:
    QTimer * timer;
    QPixmap pacman;
};

#endif // ACTOR_H
