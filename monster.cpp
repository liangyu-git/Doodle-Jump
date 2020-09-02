#include "monster.h"
#include "doodle.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

Monster::Monster(int x, int y):QObject(),QGraphicsPixmapItem()
{
    placeX = x;
    placeY = y;
    setPos(x,y);
    setPixmap(QPixmap(":/resource/pic/plate.png").scaledToWidth(70));
    // qDebug()<<"plate spawn : "<<x<<" "<<y;
}

void Monster::setNewPos(double x, double y)
{
    placeX = x;
    placeY = y;
    setPos(x,y);
    // qDebug() << "set newPos function called";
}
