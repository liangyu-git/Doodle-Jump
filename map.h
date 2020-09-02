#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

#include "plate.h"
#include "monster.h"

class Map: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Map(QGraphicsScene *sceneIn);
    Plate *plate[8], *initialPlate[8], *whitePlate[2];
    Plate *rocketPlate, *hatPlate;
    Plate *shieldPlate;
    Plate *black;
    Plate *wood;
    Monster *monster[4];
    int plateX, plateY;
    double doodleHeight;
    QGraphicsTextItem *scoreText, *dead;
    QGraphicsScene *scene;
    int score = 0;
    QTimer *moveTimer;
    void setPlates();
    double moveMap(double dy);
    int nowMonster = 4;

public slots:
    // void moveMapSlot(double height);
};

#endif // MAP_H
