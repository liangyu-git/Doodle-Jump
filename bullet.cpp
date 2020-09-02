#include "bullet.h"
#include "plate.h"
#include "monster.h"

Bullet::Bullet()
{
    QTimer *bulletTimer = new QTimer();
    bulletTimer->start(2);
    setPixmap(QPixmap(":/resource/pic/fireball.png").scaled(15,40));
    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(shoot()));
}

void Bullet::shoot()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Monster)){
            scene()->removeItem(colliding_items[i]);
            colliding_items[i]->setPos(0,-500);
            scene()->removeItem(this);
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    setPos(x(), y()-3);
    if(y()+40 < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}
