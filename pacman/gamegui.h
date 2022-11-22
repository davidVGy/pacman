#ifndef GAMEGUI_H
#define GAMEGUI_H
#include <QWidget>
#include "actor.h"
#include "cookie.h"
#include <QGraphicsView>
#include <QMediaPlayer>

#define ZOOM 2

class gamegui : public QGraphicsView
{
    Q_OBJECT

public:
    gamegui(QWidget * parent = 0);
    Actor * actor;
    Cookie **cookie;


public slots:
    void cookieAte();

private:
    int *statuscookies;
    int numcookies;
    QMediaPlayer * music;

};

#endif // GAMEGUI_H
