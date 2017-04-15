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
#include "mainAnimal.hpp"
//class MainAnimal;

class Simulation : public QGraphicsScene {
  Q_OBJECT
  //QThread simu_thread;
  public:
    Simulation(QObject *parent = 0);
    ~Simulation();
    void start_simulation();
    void terminate_simulation();

  signals:
    void signal_passeuntour();

  public slots:
    void slot_setTailleX(int);
    void slot_setTailleY(int);
    void slot_simulation_animal();
    void slot_nb_animaux(int);
    void handleResults(int x, int y, char id);
    void slot_effacer();

  private:
    QGraphicsRectItem *terrain;

    int hauteur = 0, largeur = 0;
    int tailleX = 0, tailleY = 0;

    int nb_animaux = 50;

    MainAnimal *simulation_animal;
    int resultat = 0;

    QPixmap lion;
    QPixmap gazelle;
    QPixmap gigot;
    QPixmap tombe;

    QList<QGraphicsPixmapItem*> tab_image;
    //QGraphicsPixmapItem **tab2Dimage;
    bool simu_en_cours = false;
};

#endif
