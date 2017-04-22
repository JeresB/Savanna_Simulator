#ifndef ANIMAL_H
#define ANIMAL_H

#include <cstdlib>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QDebug>
using namespace std;

class Simulation;

class Animal : public QGraphicsPixmapItem {
  public:
    Animal(Simulation * m, int x, int y, int energie, QPixmap i);

    ~Animal();

    //int getX();
    //int getY();
    int getEnergie();
    virtual char getID() = 0;
    virtual int getNature();

    //void setX(int x);
    //void setY(int y);
    //void setPos(int x, int y);
    virtual void setID(char id_set) = 0;
    void setEnergie(int energie);
    virtual void setNature(int n);

    void affiche();

    void bouge(int sens);

  protected :
    //int x, y;
    int energie;
    int taille;
    Simulation * monde;
    char id = 'A';
    int nature_naissance;
};

#endif
