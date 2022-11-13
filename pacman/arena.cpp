#include "arena.h"
#include <QGraphicsTextItem>
#include <QImage>
#include "gamegui.h"

Arena::Arena()
{
    mapImg.load(":/images/img/pacman_sheet.png");

    cookieMap   = mapImg.copy(0, 0, 224, 248);
    img_bg      = mapImg.copy(228, 0, 224, 248);
}
void Arena::create_scene()
{
    //load image background and add color black in background
    scene = new QGraphicsScene();
    QPixmap     temp(img_bg.size());
    temp.fill(Qt::transparent);
    QPainter p(&temp);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, img_bg);
    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p.fillRect(temp.rect(), Qt::black);
    p.end();
    img_bg = temp;

    //get info color pixel image, before convert in QImage

    //edit image and push like background
    img_bg = img_bg.scaled((ZOOM * img_bg.size()), Qt::KeepAspectRatio);
    scene->setSceneRect(0, 0, img_bg.width(), img_bg.height());
    scene->setBackgroundBrush(QBrush(img_bg));

}

void Arena::get_walls()
{
    QImage img_temp;
    img_temp = img_bg.toImage();
    walls.resize(img_bg.height(), vector<int>(img_bg.width()));
    QRgb colorRGB;
    for(int y = 0; y < img_bg.height(); y++){
        for(int x = 0; x < img_bg.width(); x++){
            colorRGB = img_temp.pixel(x,y);
            if (colorRGB == 0xff2121ff)
                walls[y][x] = 1;
            else
                walls[y][x] = 0;
        }
    }
}

void Arena::get_cookies()
{
    QImage img_temp;
    img_temp = cookieMap.toImage();
    posCookies.resize(cookieMap.height(), vector<int>(2));
    QRgb colorRGB;
    for(int y = 0; y < cookieMap.height(); y++){
        for(int x = 0; x < cookieMap.width(); x++){
            colorRGB = img_temp.pixel(x,y);
            if (colorRGB == 0xfffab9b0 && ((y - 4) % 8 == 0 && (x - 4) % 8 == 0))
            {
                posCookies[Cknum][0] = y - 1;
                posCookies[Cknum][1] = x - 1;
                Cknum++;
            }
        }
    }
}
