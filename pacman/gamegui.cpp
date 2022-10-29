#include "gamegui.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

gamegui::gamegui(QWidget * parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1000,900); // make the scene 800x600 instead of infinity by infinity (default)

      // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
      // it can be used to visualize scenes)
      setScene(scene);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setFixedSize(800,600);

      // create the player
    actor = new Actor();
    actor->setPos(400,500); // TODO generalize to always be in the middle bottom of screen
      // make the player focusable and set it to be the current focus
      actor->setFlag(QGraphicsItem::ItemIsFocusable);
      actor->setFocus();
      // add the player to the scene
      scene->addItem(actor);


      // play background music
//      QMediaPlayer * music = new QMediaPlayer();
//      music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
//      music->play();

      show();
}
