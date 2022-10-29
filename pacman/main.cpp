#include <QCoreApplication>
#include <QApplication>
#include <QtWidgets>
#include "gamegui.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gamegui game;
    game.show();
    return a.exec();
}
