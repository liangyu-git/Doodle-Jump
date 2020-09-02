#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Monster: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Monster(int x = 0,int y = 0);
    double placeX, placeY;
    void setNewPos(double x, double y);
};


#endif // MONSTER_H
