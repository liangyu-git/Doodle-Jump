#include "plate.h"
#include "doodle.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

Plate::Plate(int x, int y):QObject(),QGraphicsPixmapItem()
{
    placeX = x;
    placeY = y;
    setPos(x,y);
    setPixmap(QPixmap(":/resource/pic/plate.png").scaled(50,12));
    // qDebug()<<"plate spawn : "<<x<<" "<<y;
}

void Plate::setNewPos(double x, double y)
{
    placeX = x;
    placeY = y;
    setPos(x,y);
    // qDebug() << "set newPos function called";
}
