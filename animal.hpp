#ifndef ANIMAL_H
#define ANIMAL_H

#include <cstdlib>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
using namespace std;

class Simulation;

class Animal : public QGraphicsPixmapItem {
  public:
    Animal(Simulation * m, int x, int y, int energie, QPixmap i);

    ~Animal();

    //int getX();
    //int getY();
    int getEnergie();

    //void setX(int x);
    //void setY(int y);
    //void setPos(int x, int y);
    void setEnergie(int energie);

    void affiche();

    void bouge();

  private :
    //int x, y;
    int energie;
    int taille;
    Simulation * monde;
};

#endif
