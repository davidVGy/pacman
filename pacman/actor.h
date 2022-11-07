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
    enum stateKey {IDLE, RIGHT, LEFT, UP, DOWN} keypress = IDLE, keypress_next = IDLE;
    vector<vector<int>> map;
    Actor(Arena *mapGame, QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);
    void create_pacman();
    void collide();

public slots:
    void move();

private:
    QTimer * timer;
    QPixmap pacman;
    QPixmap pixmap;
    int canMoveYtoX = 0;
    int canMoveXtoY = 0;
    int moveX = 0;
    int moveY = 0;
    int changeXtoY = 0;
    int changeYtoX = 0;
    int canTurn = 0;
    int changeDirection = 0;
};

#endif // ACTOR_H
