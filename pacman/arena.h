#ifndef ARENA_H
#define ARENA_H
#include <QGraphicsView>
#include <vector>

using namespace std;

class Arena: public QGraphicsView
{
public:
    Arena();
    void create_scene();
    void  get_walls();
    QGraphicsScene * scene;
    QPixmap img_bg;
    QPixmap mapImg;
    vector<vector<int>> walls;
    QPixmap cookieMap;
    vector<vector<int>> posCookies;
    int Cknum = 0;
    void get_cookies();

};

#endif // ARENA_H
