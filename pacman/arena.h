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
    vector<vector<int>> walls;
};

#endif // ARENA_H
