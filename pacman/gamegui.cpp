#include "gamegui.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QImage>
#include "arena.h"
#include "cookie.h"
#include "game.h"
#include <QObject>
#include <iostream>
#include <QMediaPlayer>

gamegui::gamegui(QWidget * parent)
{
    Arena arena;
    arena.create_scene();
    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(arena.scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(arena.img_bg.width() + 2, arena.img_bg.height() + 2);

    arena.get_cookies();
//    Cookie *cookie[arena.Cknum];
    cookie = new Cookie*[arena.Cknum];
    for (int i = 0; i < arena.Cknum; ++i) {
        cookie[i] = new Cookie();
        cookie[i]->create_cookie();
        cookie[i]->setPos(arena.posCookies[i][1]*ZOOM, arena.posCookies[i][0]*ZOOM);
        arena.scene->addItem(cookie[i]);
    }

    // create the player
    actor = new Actor(&arena, 0);
    actor->create_pacman();
    actor->setPos(104*ZOOM,180*ZOOM); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    actor->setFlag(QGraphicsItem::ItemIsFocusable);
    actor->setFocus();
    // add the player to the scene
    arena.scene->addItem(actor);

    connect(actor, &Actor::valueChanged, this, &gamegui::cookieAte);
    statuscookies = (int*)calloc(arena.Cknum, sizeof(int));
    numcookies = arena.Cknum;

      // play background music
      music = new QMediaPlayer();
      music->setSource(QUrl("qrc:/images/sounds/sounds/Pacman siren.mp3"));
//      music->loops();
      music->setLoops(QMediaPlayer::Infinite);
      music->play();

}

void gamegui::cookieAte()
{

    for(int i = 0; i < numcookies; i++)
    {
        if(!statuscookies[i])
        {
            if(cookie[i]->collidesWithItem(actor, Qt::IntersectsItemBoundingRect))
            {
                delete(cookie[i]);
                statuscookies[i] = 1;
//                      music->setSource(QUrl("qrc:/images/sounds/sounds/Pacman Waka Waka.mp3"));
//                      music->play();
            }
        }
    }
}

