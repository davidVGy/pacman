#include "cookie.h"
#include <qpainter.h>
#include <QGraphicsPixmapItem>
#include "gamegui.h"

Cookie::Cookie(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{

}

void Cookie::create_cookie()
{
   QRgb colorCookie = 0xfffab9b0;
   elCookie = new QPixmap(2*ZOOM, 2*ZOOM);
   elCookie->fill(colorCookie);
   setPixmap(*elCookie);

}

