#include "Animal.hpp"
#include "Simulation.hpp"

Animal::Animal(Simulation * m, int x, int y, int energie, QPixmap i) : energie(energie){
  this->monde = m; // On défini le monde de l'animal
  this->setPos(x, y); // On initialise la position de l'image
  this->setPixmap(i); // On initialise l'image
  taille = i.width(); // On récupère la taille de l'image
}

int Animal::getEnergie(){
  return this->energie;
}

void Animal::setEnergie(int energie){
  this->energie = energie;
}

void Animal::bouge(int sens) {
  int speed = 1; // Vitesse des animaux

  // Si le sens vaut -1 aucun déplacement intelligent n'est à faire
  if(sens == -1) sens = rand() % 4; // Donc on choisi un sens aléatoire
  if(this->getID() == 'L') speed = 2;
  switch(sens) { // Direction
    case 0:
      // Ouest
      if (this->x() > monde->borderLeft()) this->setX(this->x() - speed);
      break;
    case 1:
      // Est
      if (this->x() + taille < monde->borderRight()) this->setX(this->x() + speed);
      break;
    case 2:
      // Nord
      if (this->y() > monde->borderTop()) this->setY(this->y() - speed);
      break;
    case 3:
      // Sud
      if (this->y() + taille < monde->borderBottom()) this->setY(this->y() + speed);
      break;
  }

  // L'animal perd de l'énergie après son déplacement
  energie--;

  // Si l'énergie atteint 0
  if (energie == 0) {
    // Si c'est un lion alors on décrémente le nombre de lion en vies
    if(this->getID() == 'L') monde->setLion(monde->getLion() - 1);
    // Si c'est une gazelle alors on décrémente le nombre de gazelle en vies
    else if(this->getID() == 'G') monde->setGazelle(monde->getGazelle() - 1);

    // On définie l'image "mort" à la plce de l'animal
    this->setPixmap(monde->getImageMort());
    // On déclare son id à X
    this->setID('X');
    // On incrémente le nombre d'animaux morts
    monde->setMort(monde->getMort() + 1);
  }
}
