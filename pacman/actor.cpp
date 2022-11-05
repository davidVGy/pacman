#include "actor.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QPainter>
#include <QTimer>
#include <stdlib.h> // rand() -> really large int
#include "arena.h"
#include <iostream>

Actor::Actor(Arena *mapGame, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    mapGame->get_walls();
    map = mapGame->walls;

    // drew the rect
    QPixmap pixmap(":/images/img/pacman_sheet.png");
    pacman = pixmap.copy(473,1,12,13);
    pacman = pacman.scaled(2*pacman.size(),Qt::KeepAspectRatio);
    setPixmap(pacman);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer -> start(12);


}

void Actor::move()
{
    int pos_x = pos().x();
    int pos_y = pos().y();
//    static int pos_back[2];
//    pos_back[0] = pos_x;
//    pos_back[1] = pos_y;
    if (keypress == LEFT){
        if (map[pos_y][pos_x] == 0 && map[pos_y][pos_x - 1] == 0)
        setPos(x() - 1,y());
    }
    else if (keypress == RIGHT){
        pos_x += pacman.width();
        if (map[pos_y][pos_x] == 0 && map[pos_y][pos_x + 1] == 0)
        setPos(x() + 1,y());
    }
    else if (keypress == UP){
        if (map[pos_y][pos_x] == 0 && map[pos_y - 1][pos_x] == 0)
        setPos(x(),y() - 1);
    }
    else if (keypress == DOWN){
        pos_y += pacman.height();
        if (map[pos_y][pos_x] == 0 && map[pos_y + 1][pos_x] == 0)
        setPos(x(),y() + 1);
    }
}

void Actor::keyPressEvent(QKeyEvent * event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        keypress = LEFT;
    }
    else if (event->key() == Qt::Key_Right){
        keypress = RIGHT;
    }
    else if (event->key() == Qt::Key_Up){
        keypress = UP;
    }
    else if (event->key() == Qt::Key_Down){
        keypress = DOWN;
    }

    // shoot with the spacebar
//    else if (event->key() == Qt::Key_Space){
//        // create a bullet
//        Bullet * bullet = new Bullet();
//        bullet->setPos(x()+45,y());
//        scene()->addItem(bullet);

//        // play bulletsound
//        if (bulletsound->state() == QMediaPlayer::PlayingState){
//            bulletsound->setPosition(0);
//        }
//        else if (bulletsound->state() == QMediaPlayer::StoppedState){
//            bulletsound->play();
//        }

//    }
}
