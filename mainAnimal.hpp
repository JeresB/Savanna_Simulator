#ifndef MAINANIMAL_H
#define MAINANIMAL_H

#include "Animal.hpp"
#include "Monde.hpp"
#include "Lion.hpp"
#include "Gazelle.hpp"
#include <vector>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QTimer>
//#include "simulation.hpp"
//class Simulation;

class MainAnimal : public QThread {
  Q_OBJECT

  public:
    MainAnimal();
    ~MainAnimal();
    //void setSimulation(Simulation *simu);
    void setNbAnimaux(int nb_anim);
    void setTailleX(int x);
    void setTailleY(int y);

  public slots:
      void doWork();
      void run();
      void update();

  signals:
    void resultReady(int, int, char);
    void effacer();

  private:
    //Simulation *resultSimu;
    int nb_animaux = 50;
    int max_x = 50;
    int max_y = 20;
    Monde *monde;
    QTimer *timer;
};

#endif
