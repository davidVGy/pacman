#include "gamegui.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QImage>
#include "arena.h"


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

    // create the player
    actor = new Actor(&arena, 0);
    actor->create_pacman();
    actor->setPos(4*ZOOM,4*ZOOM); // TODO generalize to always be in the middle bottom of screen
      // make the player focusable and set it to be the current focus
      actor->setFlag(QGraphicsItem::ItemIsFocusable);
      actor->setFocus();
      // add the player to the scene
      arena.scene->addItem(actor);


      // play background music
//      QMediaPlayer * music = new QMediaPlayer();
//      music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
//      music->play();

      show();
}
