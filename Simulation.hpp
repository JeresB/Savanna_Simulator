#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QRectF>
#include <QMediaPlayer>
#include <cmath>
#include <QSound>
#include "Animal.hpp"
#include "Statistiques.hpp"

#define FREQUENCE_NATURE 1000

class Simulation : public QGraphicsScene {
  Q_OBJECT
  public:
    Simulation(Statistiques* stats, QObject *parent = 0);
    ~Simulation(){};

    // Getters
    QPixmap getImageMort();
    int getLion();
    int getGazelle();
    int getMort();

    // Setters
    void setLion(int l);
    void setGazelle(int g);
    void setMort(int m);

    // Retourne les positions des bordures du terrain de la simulation
    int borderLeft();
    int borderRight();
    int borderTop();
    int borderBottom();

    // Méthodes
    void terminer();
    void peuplement();
    int plus_proche(int a);
    int deplacement_intelligent(int a1, int a2);
    void affrontement(int animal);
    void nature(int indice);

  signals:
    void signal_valeurs(int, int, int, int, int);

  public slots:
    void slot_nb_animaux(int);
    void slot_setProportion(int);
    void slot_vitesse(int);
    void slot_setEnergie(int);
    void slot_setTailleX(int);
    void slot_setTailleY(int);
    void slot_simulation();

    void update();

  private:
    QGraphicsRectItem *terrain;
    Statistiques* statsWindow;

    QTimer *timer;

    QVector<Animal*> vect_animaux;

    bool simu_en_cours = false;

    int tailleX = 0, tailleY = 0;

    int nb_animaux = 50;
    int proportion = 2;
    int vitesse = 20;
    int energie = 200;

    int sens = -1;
    int nature_naissance = 0;

    int lion_vivant = 0, gazelle_vivante = 0, vegetal_vivant = 0;
    int animaux_mort = 0, gazelle_mange = 0;

    QPixmap lion;
    QPixmap gazelle;
    QPixmap vegetal;
    QPixmap gigot;
    QPixmap tombe;

    QSound* musique;
};

#endif
