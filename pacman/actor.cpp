#include "actor.h"
#include <QImage>
#include <QPixmap>

Actor::Actor()
{
    QImage pacman
    pacman.load("img/pacman_sheet","png");

    picture=QPixmap("C:\\Board").scaled(600,600,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
   setFixedSize(picture.size());

}
