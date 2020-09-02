#include "doodle.h"
#include "plate.h"

#include <QList>
#include <QDebug>

Doodle::Doodle(QGraphicsScene *scene)
{
    setPixmap(QPixmap(":/resource/pic/left.png").scaledToWidth(50));
    scene->addItem(this);
    this->setPos(175, 300);
    map = new Map(scene);
    QTimer *jumpTimer = new QTimer();
    jumpTimer->start(5);
    connect(jumpTimer,SIGNAL(timeout()),this,SLOT(jump()));
    // connect(this,SIGNAL(needToMove(double)),map,SLOT(moveMapSlot(double)));
}

void Doodle::jump()
{
//    int i, n;
//    QList<QGraphicsItem *> colliding_items = collidingItems();
//    for (i = 0, n = colliding_items.size(); i < n; ++i){
//        if (typeid(*(colliding_items[i])) == typeid(Plate) && dy>0){
//            plateHeight = colliding_items[i]->y();
//            dy = -10;
//        }
//    }



    if(mode == NOTHING)
    {
        for(int i = 0; i<8; i++) {
            if(y()+50>map->plate[i]->placeY && y()+50<map->plate[i]->placeY+9
                    && x()+50>map->plate[i]->placeX && x()<map->plate[i]->placeX+32
                    && y()>0
                    && dy>0)
            {
                // qDebug() << "plate " << i;
                dy = -2;
                plateHeight = map->plate[i]->y();
            }
        }
        for(int i = 0; i<8; i++) {
            if(y()+50>map->initialPlate[i]->placeY
                    && y()+50<map->initialPlate[i]->placeY+12
                    && x()+50>map->initialPlate[i]->placeX
                    && x()<map->initialPlate[i]->placeX+32
                    && dy>0)
            {
                // qDebug() << "plate " << i;
                dy = -2;
                // plateHeight = map->plate[i]->y();
            }
        }
        if(y()+50>map->wood->placeY && y()+50<map->wood->placeY+9
                && x()+50>map->wood->placeX && x()<map->wood->placeX+32
                && y()>0
                && dy>0)
        {
            map->wood->setPixmap(QPixmap(":/resource/pic/brokenWood.png").scaled(50,20));
        }
        for(int i = 0; i<2; i++) {
            if(y()+50>map->whitePlate[i]->placeY
                    && y()+50<map->whitePlate[i]->placeY+12
                    && x()+50>map->whitePlate[i]->placeX
                    && x()<map->whitePlate[i]->placeX+32
                    && dy>0)
            {
                // qDebug() << "plate " << i;
                dy = -2;
                map->whitePlate[i]->setNewPos(x(),-20);
                // plateHeight = map->plate[i]->y();
            }
        }
        if(y()+50>map->hatPlate->placeY
                && y()<map->hatPlate->placeY+20
                && x()+50>map->hatPlate->placeX
                && x()<map->hatPlate->placeX+32
                )
        {
            mode = HAT;
            dy = -2;
            moveArg = -7;
            this->setPixmap(QPixmap(":/resource/pic/withHat.png").scaledToWidth(50));
        }
        if(y()+50>map->rocketPlate->placeY
                && y()<map->rocketPlate->placeY+115
                && x()+50>map->rocketPlate->placeX
                && x()<map->rocketPlate->placeX+32
                )
        {
            mode = ROCKET;
            dy = -2;
            moveArg = -10;
            this->setPixmap(QPixmap(":/resource/pic/withRocket.png").scaled(65,135));
        }
        if(y()+50>map->shieldPlate->placeY
                && y()<map->shieldPlate->placeY+20
                && x()+50>map->shieldPlate->placeX
                && x()<map->shieldPlate->placeX+32
                )
        {
            dy = -2;
            SHIELD = true;
            this->setPixmap(QPixmap(":/resource/pic/doodleShield.png").scaledToWidth(70));
            map->shieldPlate->setNewPos(map->shieldPlate->placeX,-1500);
        }
        if(y()+50>map->black->placeY
                && y()<map->black->placeY+20
                && x()+50>map->black->placeX
                && x()<map->black->placeX+40
                )
        {
            mode = DEAD;
            qDebug()<<"DEAD black";
        }
        for(int i = 0; i<4; ++i)
        {
            if(y()+50>map->monster[i]->placeY
                && y()<map->monster[i]->placeY+40
                && x()+50>map->monster[i]->placeX
                && x()<map->monster[i]->placeX+40
                && SHIELD == false
                )
            {
                mode = DEAD;
                qDebug()<<"DEAD monster";
            }
            if(y()+50>map->monster[i]->placeY
                && y()<map->monster[i]->placeY+40
                && x()+50>map->monster[i]->placeX
                && x()<map->monster[i]->placeX+40
                && SHIELD == true
                )
            {
                this->setPixmap(QPixmap(":/resource/pic/left.png").scaledToWidth(50));
                map->monster[i]->setNewPos(map->monster[i]->x(),-2000);
                SHIELD = false;
            }
        }
    }

    if(x()>400) {
        this->setPos(0,y());
    }
    if(x()<-50) {
        this->setPos(350,y());
    }
    if(y() < 230 && dy<0 && mode == NOTHING)
    {
        dy = map->moveMap(dy);
        setPos(x(),229);
//        if(dy > 0)
//        {
//            dy+=0.01;
//            setPos(x(),230+dy);
//        }
    }else if(mode == NOTHING)
    {
        dy+=0.01;
        setPos(x(),y()+dy);
    }
    if(mode == HAT) {
        moveArg+=0.01;
        dy = map->moveMap(moveArg);
        if(y()>250)
        {
            setPos(x(),y()-1);
        }else if(y()<250)
        {
            setPos(x(),y()+1);
        }else
        {
            setPos(x(),y());
        }
        if(dy>=0)
        {
            mode = NOTHING;
            if(SHIELD == false)
                this->setPixmap(QPixmap(":/resource/pic/left.png").scaledToWidth(50));
            else {
                this->setPixmap(QPixmap(":/resource/pic/doodleShield.png").scaledToWidth(70));
            }
        }
    }
    if(mode == ROCKET) {
        moveArg+=0.01;
        dy = map->moveMap(moveArg);
        if(y()>250)
        {
            setPos(x(),y()-1);
        }else if(y()<250)
        {
            setPos(x(),y()+1);
        }else
        {
            setPos(x(),y());
        }
        if(dy>=0)
        {
            mode = NOTHING;
            if(SHIELD == false)
                this->setPixmap(QPixmap(":/resource/pic/left.png").scaledToWidth(50));
            else {
                this->setPixmap(QPixmap(":/resource/pic/doodleShield.png").scaledToWidth(70));
            }
        }
    }
    // qDebug()<<"dy : "<<dy;
    // death
    if(mode == DEAD)
    {
        setPos(x(),y()+2);
        if(y()>500) {
            delete this;
            map->dead->setPos(100,200);
            map->scoreText->setPos(150,300);
            return;
        }
    }
    if(y()>500) {
        delete this;
        map->dead->setPos(100,200);
        map->scoreText->setPos(150,300);
    }
}
