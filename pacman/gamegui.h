#ifndef GAMEGUI_H
#define GAMEGUI_H
#include <QWidget>
#include "actor.h"
#include <QGraphicsView>

#define ZOOM 2

class gamegui : public QGraphicsView
{
    Q_OBJECT

public:
    gamegui(QWidget * parent = 0);
    Actor * actor;

private:

};

#endif // GAMEGUI_H
