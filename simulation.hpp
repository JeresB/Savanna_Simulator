#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QMetaType>
#include <QTimer>
#include <QRectF>
#include "animal.hpp"

class Simulation : public QGraphicsScene {
  Q_OBJECT
  public:
    Simulation(QObject *parent = 0);
    ~Simulation();

    int getMAX_X();
    int getMAX_Y();

    int borderLeft();
    int borderRight();
    int borderTop();
    int borderBottom();

    void peuplement();

  signals:
    //void signal_passeuntour();

  public slots:
    void slot_setTailleX(int);
    void slot_setTailleY(int);
    void slot_nb_animaux(int);
    void slot_vitesse(int);
    void slot_setEnergie(int);
    void slot_simulation_animal();

    void update();

  private:
    QGraphicsRectItem *terrain;

    int hauteur = 0, largeur = 0;
    int tailleX = 0, tailleY = 0;

    int nb_animaux = 50;
    int energie = 300;
    int sens = 10;
    int vitesse = 100;

    QPixmap lion;
    QPixmap gazelle;
    QPixmap gigot;
    QPixmap tombe;

    QVector<Animal*> tab_anim;
    bool simu_en_cours = false;

    Animal * leopard;

    QTimer *timer;
};

#endif
