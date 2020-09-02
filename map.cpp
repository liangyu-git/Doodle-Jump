#include "map.h"
#include "mainwindow.h"

#include <cstdlib>
#include <QDebug>
#include <QString>

Map::Map(QGraphicsScene *sceneIn)
{
    scene = sceneIn;
    for(int i=0; i<8; i++){
        plate[i] = new Plate(50*i,12);
        scene->addItem(plate[i]);

        initialPlate[i] = new Plate(50*i,488);
        scene->addItem(initialPlate[i]);
    }
    for(int i = 0; i<2; ++i) {
        whitePlate[i] = new Plate(50*i, -20);
        whitePlate[i]->setPixmap(QPixmap(":/resource/pic/white.png"));
        scene->addItem(whitePlate[i]);
    }

    for(int i = 0; i<4; ++i) {
        monster[i] = new Monster(50*i, -100);
        monster[i]->setPixmap(QPixmap(":/resource/pic/monster1.png").scaledToWidth(70));
        // dscene->addItem(monster[i]);
    }
    rocketPlate = new Plate(0,-1400);
    rocketPlate->setPixmap(QPixmap(":/resource/pic/rocket.png").scaled(60,130));
    scene->addItem(rocketPlate);
    hatPlate = new Plate(0,-700);
    hatPlate->setPixmap(QPixmap(":/resource/pic/hat.png").scaled(50,35));
    scene->addItem(hatPlate);
    shieldPlate = new Plate(20,-600);
    shieldPlate->setPixmap(QPixmap(":/resource/pic/withShield.png").scaled(50,60));
    scene->addItem(shieldPlate);
    black = new Plate(20,-2000);
    black->setPixmap(QPixmap(":/resource/pic/black.png").scaledToWidth(60));
    scene->addItem(black);
    wood = new Plate(20,-200);
    wood->setPixmap(QPixmap(":/resource/pic/wood.png").scaled(50,14));
    scene->addItem(wood);

    scoreText = new QGraphicsTextItem();
    // scoreText->setPlainText(QString("Score : ") + QString::number(score));
    scoreText->setDefaultTextColor(Qt::blue);
    scoreText->setFont(QFont("consolars",15));
    scoreText->setPos(0,0);
    scene->addItem(scoreText);
    dead = new QGraphicsTextItem();
    dead->setPlainText("GAME OVER");
    dead->setDefaultTextColor(Qt::red);
    dead->setFont(QFont("consolars",25));
    dead->setPos(100,-200);
    scene->addItem(dead);
}

void Map::setPlates()
{
    srand(time(NULL));
    for(int i=0; i<8; i++){
        plateY = 500-i*62;
        plateX = rand()%350;
        plate[i]->setNewPos(plateX,plateY);
    }
    for(int i = 0; i<2; ++i) {
        whitePlate[i]->setNewPos(plateX,200*i);
    }
}

//void Map::moveMap()
//{
//    srand(time(NULL));
//    // qDebug()<<"moveMap";
//    int randX;
//    if(doodleHeight<350) {
//        for(int i=0; i<8; i++){
//            plate[i]->setNewPos(plate[i]->x(),plate[i]->y()+1);
//            initialPlate[i]->setNewPos(1000,0);
//        }
//        for(int i=0; i<2; i++){
//            whitePlate[i]->setNewPos(whitePlate[i]->x(),whitePlate[i]->y()+1);
//        }
//        score++;
//        scoreText->setPlainText(QString("Score : ") + QString::number(score));
//        doodleHeight+=200;
//    }

//    // qDebug()<<"in moveMap() doodleHeight : "<<doodleHeight;
//    for(int i = 0; i<8; ++i) {
//        randX = rand()%350;
//        if(plate[i]->y()>500) {
//            plate[i]->setNewPos(randX,0);
//        }
//    }
//    for(int i = 0; i<2; ++i) {
//        randX = rand()%350;
//        if(whitePlate[i]->y()>500) {
//            whitePlate[i]->setNewPos(randX,0);
//        }
//    }
//}

//void Map::moveMapSlot(double height)
//{
//    doodleHeight = height;
//    moveTimer = new QTimer();
//    moveTimer->start(50);
//    connect(moveTimer,SIGNAL(timeout()),this,SLOT(moveMap()));
//    // qDebug()<<"moveMapSlot";
//}

double Map::moveMap(double dy)
{
    srand(time(NULL));
    int randX;
    for(int i=0; i<8; i++){
        plate[i]->setNewPos(plate[i]->x(),plate[i]->y()-dy);
        initialPlate[i]->setNewPos(1000,0);
    }
    for(int i=0; i<2; i++){
        whitePlate[i]->setNewPos(whitePlate[i]->x(),whitePlate[i]->y()-dy);
    }
    hatPlate->setNewPos(hatPlate->x(),hatPlate->y()-dy);
    rocketPlate->setNewPos(rocketPlate->x(),rocketPlate->y()-dy);
    shieldPlate->setNewPos(shieldPlate->x(),shieldPlate->y()-dy);
    black->setNewPos(black->x(),black->y()-dy);
    wood->setNewPos(wood->x(),wood->y()-dy);

    if(score%1500 == 0) {
        randX = rand()%4;
        monster[randX]->setNewPos(randX*100,-200);
        nowMonster = randX;
        switch (nowMonster) {
        case 0:
            monster[nowMonster]->setPixmap(QPixmap(":/resource/pic/monster1.png").scaledToWidth(70));
            scene->addItem(monster[nowMonster]);
            break;
        case 1:
            monster[nowMonster]->setPixmap(QPixmap(":/resource/pic/monster2.png").scaledToWidth(70));
            scene->addItem(monster[nowMonster]);
            break;
        case 2:
            monster[nowMonster]->setPixmap(QPixmap(":/resource/pic/monster3.png").scaledToWidth(70));
            scene->addItem(monster[nowMonster]);
            break;
        case 3:
            monster[nowMonster]->setPixmap(QPixmap(":/resource/pic/monster4.png").scaledToWidth(70));
            scene->addItem(monster[nowMonster]);
            break;
        }
    }
    if(nowMonster != 4)
    {
        monster[nowMonster]->setNewPos(monster[nowMonster]->x(),monster[nowMonster]->y()-dy);
    }
    // qDebug()<<"in moveMap() doodleHeight : "<<doodleHeight;
    for(int i = 0; i<8; ++i) {
        randX = rand()%350;
        if(plate[i]->y()>500) {
            plate[i]->setNewPos(randX,0);
        }
    }
    dy+=0.02;
    score++;
    scoreText->setPlainText(QString("Score : ") + QString::number(score));
    for(int i = 0; i<2; ++i) {
        randX = rand()%350;
        if(whitePlate[i]->y()>500) {
            whitePlate[i]->setNewPos(randX,0);
        }
    }
    if(rocketPlate->y()>500) {
        randX = rand()%350;
        rocketPlate->setNewPos(randX,-1900);
    }
    if(hatPlate->y()>500) {
        randX = rand()%350;
        hatPlate->setNewPos(randX,-100);
    }
    if(shieldPlate->y()>500) {
        randX = rand()%350;
        shieldPlate->setNewPos(randX,-900);
    }
    if(black->y()>500) {
        randX = rand()%350;
        black->setNewPos(randX,-2000);
    }
    if(wood->y()>500) {
        randX = rand()%350;
        wood->setNewPos(randX,-200);
        wood->setPixmap(QPixmap(":/resource/pic/wood.png"));
    }
    if(nowMonster!=4 && monster[nowMonster]->y()>500) {
        monster[nowMonster]->setNewPos(monster[nowMonster]->x(),-100);
        scene->removeItem(monster[nowMonster]);
        nowMonster = 4;
    }
    return dy;
}
