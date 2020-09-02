#ifndef DOODLE_H
#define DOODLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

#include "map.h"

#define NOTHING 0
#define HAT 1
#define ROCKET 2
#define DEAD 3

class Doodle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Doodle(QGraphicsScene *scene);
    Map *map;
    double dy;
    double plateHeight = 400;
    int mode;
    double moveArg;
    bool SHIELD = false;
signals:
    void needToMove(double plateHeight);

public slots:
    void jump();
};

#endif // DOODLE_H
