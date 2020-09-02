#ifndef PLATE_H
#define PLATE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Plate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Plate(int x = 0,int y = 0);
    double placeX, placeY;
    void setNewPos(double x, double y);
};

#endif // PLATE_H
