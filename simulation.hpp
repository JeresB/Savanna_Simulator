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
#include <QTime>
#include <QRectF>
#include "animal.hpp"
#include "statistiques.hpp"

class Simulation : public QGraphicsScene {
  Q_OBJECT
  public:
    Simulation(QObject *parent = 0);
    ~Simulation();

    int getMAX_X();
    int getMAX_Y();
    QPixmap getImageMort();
    int getLion();
    int getGazelle();

    void setLion(int l);
    void setGazelle(int g);

    int borderLeft();
    int borderRight();
    int borderTop();
    int borderBottom();

    void peuplement();
    void affrontement(int animal);
    void terminer();

  signals:
    void signal_valeurs(int, int, int);

  public slots:
    void slot_setTailleX(int);
    void slot_setTailleY(int);
    void slot_nb_animaux(int);
    void slot_setProportion(int);
    void slot_vitesse(int);
    void slot_setEnergie(int);
    void slot_simulation_animal(Statistiques* &statsWindow);

    void update();

  private:
    QGraphicsRectItem *terrain;

    int hauteur = 0, largeur = 0;
    int tailleX = 0, tailleY = 0;

    int nb_animaux = 50;
    int proportion = 2;
    int energie = 300;
    int sens = 10;
    int vitesse = 1000;

    int lion_vivant = 0, gazelle_vivante = 0;

    QPixmap lion;
    QPixmap gazelle;
    QPixmap gigot;
    QPixmap tombe;

    QVector<Animal*> tab_anim;
    bool simu_en_cours = false;

    Animal * leopard;

    QTimer *timer;
    QTime temps_simulation;
    int temps = 0;
};

#endif
