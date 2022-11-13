#ifndef COOKIE_H
#define COOKIE_H

#include <vector>
using namespace std;

#include <QGraphicsPixmapItem>

class Cookie: public QObject, public QGraphicsPixmapItem
{
public:

    Cookie(QGraphicsItem * parent = 0);
    void create_cookie();
    QPixmap *elCookie;
};

#endif // COOKIE_H
