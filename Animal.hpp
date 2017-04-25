#ifndef ANIMAL_H
#define ANIMAL_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Simulation;

class Animal : public QGraphicsPixmapItem {
  public:
    Animal(Simulation * m, int x, int y, int energie, QPixmap i);
    ~Animal(){};

    // Getters
    int getEnergie();
    virtual char getID() = 0;

    // Setters
    void setEnergie(int energie);
    virtual void setID(char id_set) = 0;

    void bouge(int sens);

  protected :
    int energie; // Energie de l'animal
    int taille; // Taille de l'image
    Simulation * monde; // Monde auquel appartient l'animal
    char id = 'A'; // ID de l'animal
};

#endif
