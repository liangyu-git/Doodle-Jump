#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 400, 500)),
    doodle(new Doodle(scene))
{
    srand(time(NULL));
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
    {
        doodle->setPos(doodle->x() - 15, doodle->y());
        // doodle->setPixmap(QPixmap(":/resource/pic/left.png").scaledToWidth(50));
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        doodle->setPos(doodle->x() + 15, doodle->y());
        // doodle->setPixmap(QPixmap(":/resource/pic/right.png").scaledToWidth(50));
        break;
    }
    case Qt::Key_Space:
    {
        Bullet *fire = new Bullet();
        fire->setPos(doodle->x()+23, doodle->y()-48);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(fire));
        break;
    }
    case Qt::Key_P:
    {
        break;
    }
    }
}

void MainWindow::on_startButton_clicked()
{
    doodle->map->setPlates();
    delete ui->startButton;
}
