#include "actor.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <stdlib.h> // rand() -> really large int
#include "arena.h"
#include <iostream>
#include "gamegui.h"

/*every actor is a rect of size 16x16 dynamic*/
#define W           16 * ZOOM
#define H           16 * ZOOM

/*size of actor*/
#define ACTORW      16
#define ACTORH      16

/*with this macro I change the point by chek respect the points of the rect*/
#define CHANGEPOINT   4 * ZOOM

Actor::Actor(Arena *mapGame, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    mapGame->get_walls();
    map = mapGame->walls;
    pixmap.load(":/images/img/pacman_sheet.png");
}

void Actor::create_pacman()
{
    // drew the rect
    pacman = pixmap.copy(472, 0, ACTORW, ACTORH);
    pacman = pacman.scaled((ZOOM * pacman.size()),Qt::KeepAspectRatio);
    setPixmap(pacman);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer -> start(16/ZOOM);
}

void Actor::setSprite()
{
    int pointx, pointy;
    static int count = 0;

    if(keypress == IDLE) //avoid reading array when in IDLE
    {
        return;
    }

    pointx = SPRITES[keypress][count][0];
    pointy = SPRITES[keypress][count][1];

    pacman = pixmap.copy(pointx, pointy, ACTORW, ACTORH);
    pacman = pacman.scaled((ZOOM * pacman.size()), Qt::KeepAspectRatio);
    setPixmap(pacman);

    if(count > 1) //to alternate the sequence
        count = 0;
    else
        count++;
}

void Actor::move()
{
    int pos_x           = pos().x() + 8*ZOOM;
    int pos_y           = pos().y() + 8*ZOOM;
    int mid             = 8*ZOOM;
    static int count    = 0;

    Actor::collide();

    //check the counter and if the actor is moving
    if(count == 4*ZOOM && (moveX || moveY))
    {
        Actor::setSprite();
        count = 0;
    }
    else count++;

    switch (keypress) {
    case LEFT:
        pos_x -= mid;
        //check the current pos and the future pos
        if (map[pos_y][pos_x] == 0 && map[pos_y][pos_x - 1] == 0)
        {
            setPos(x() - 1, y());
            moveX = 1;
            moveY = 0;
            return;
       }
        break;
    case RIGHT:
        pos_x += mid - 1;
        if (map[pos_y][pos_x] == 0 && map[pos_y][pos_x + 1] == 0)
        {
            setPos(x() + 1, y());
            moveX = 1;
            moveY = 0;
            return;
        }
        break;
    case UP:
        pos_y -= mid;
        if (map[pos_y][pos_x] == 0 && map[pos_y - 1][pos_x] == 0)
        {
            setPos(x(), y() - 1);
            moveX = 0;
            moveY = 1;
            return;
        }
    break;
    case DOWN:
        pos_y += mid - 1;
        if (map[pos_y][pos_x] == 0 && map[pos_y + 1][pos_x] == 0)
        {
            setPos(x(), y() + 1);
            moveX = 0;
            moveY = 1;
            return;
        }
        break;
    default:
        count = 0;  //reset counter if in IDLE
        return;
        break;
    }

    //if I arrive here is because there is a collision against the wall
    if(moveX || moveY)  //only once time after collision
    {
        //set the second sprite when there is a collision
        pacman = pixmap.copy(SPRITES[keypress][1][0], SPRITES[keypress][1][1], ACTORW, ACTORH);
        pacman = pacman.scaled((ZOOM * pacman.size()),Qt::KeepAspectRatio);
        setPixmap(pacman);
    }

    //set parameters after collision
    keypress = IDLE;
    moveX = 0;
    moveY = 0;

}

void Actor::collide()
{
    int pos_x = pos().x();
    int pos_y = pos().y();
    /*get the four points of the rect that contains the Actor*/
                         /*  y  ,  x  */
    int points[4][2] =  {{pos_y, pos_x},                    //left-up
                         {pos_y + H - 1, pos_x},            //left-down
                         {pos_y, pos_x + W - 1},            //right-up
                         {pos_y + H - 1, pos_x + W - 1}};   //right-down

    if(keypress == IDLE || keypress_next == IDLE)
    {
        return;
    }

    /*check if the position is multiple of 8, in these points the actors can turn*/
    if(((pos_y - 4*ZOOM) % (8*ZOOM)) == 0 && ((pos_x - 4*ZOOM) % (8*ZOOM)) == 0)
    {
        canTurn = 1;
    }
    else
    {
        canTurn = 0;
    }


    if(changeDirection && canTurn){           /*if I have to change direction and I can turn*/
        switch (keypress_next) {
        case LEFT:
            /*check if the two points to right of actor of 1 more position aren't a wall */
            //                 mid-left-up
            if (map[points[0][0] + CHANGEPOINT][points[0][1] - 1] == 0
                //             mid-left-down
                    && map[points[1][0] - CHANGEPOINT][points[1][1] - 1] == 0)
            {
                keypress = keypress_next;
                keypress_next = IDLE;
                changeYtoX = 0;
            }
            break;
        case RIGHT:
            //                 mid-right-up
            if (map[points[2][0] + CHANGEPOINT][points[2][1] + 1] == 0
                //             mid-right-down
                    && map[points[3][0] - CHANGEPOINT][points[3][1] + 1] == 0)
            {
                keypress = keypress_next;
                keypress_next = IDLE;
                changeYtoX = 0;
            }
            break;
        case UP:
            //              mid-left-up
            if (map[points[0][0] - 1][points[0][1] + CHANGEPOINT] == 0
                //             mid-right-up
                    && map[points[2][0] - 1][points[2][1] - CHANGEPOINT] == 0)
            {
                keypress = keypress_next;
                keypress_next = IDLE;
                changeXtoY = 0;
            }
        break;
        case DOWN:
            //              mid-left-down
            if (map[points[1][0] + 1][points[1][1] + CHANGEPOINT] == 0
                //             right-down
                    && map[points[1][0] + 1][points[1][1]] == 0
                //             mid-right-down
                    && map[points[3][0] + 1][points[3][1] - CHANGEPOINT] == 0
                //             right-down
                    && map[points[3][0] + 1][points[3][1]] == 0)            {
                keypress = keypress_next;
                keypress_next = IDLE;
                changeXtoY = 0;
            }
            break;
        default:
            break;
        }
    }
}

void Actor::keyPressEvent(QKeyEvent * event){
    // move the player left and right
    switch (event->key()) {
    case Qt::Key_Left:
        if(moveY)
        {
            keypress_next = LEFT;
            changeDirection = 1;
        }
        else
        {
            keypress = LEFT;
            changeDirection = 0;
        }
        break;
    case Qt::Key_Right:
        if(moveY)
        {
            keypress_next = RIGHT;
            changeDirection = 1;
        }
        else
        {
            keypress = RIGHT;
            changeDirection = 0;
        }
        break;
    case Qt::Key_Up:
        if(moveX)
        {
            keypress_next = UP;
            changeDirection = 1;
        }
        else
        {
            keypress = UP;
            changeDirection = 0;
        }

    break;
    case Qt::Key_Down:
        if(moveX)
        {
            keypress_next = DOWN;
            changeDirection = 1;
        }
        else
        {
            keypress = DOWN;
            changeDirection = 0;
        }
        break;
    default:
        break;
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

void Actor::cookieAte()
{
//    bool coll = actor->collidesWithItem(cookie[5], Qt::IntersectsItemShape);
}
