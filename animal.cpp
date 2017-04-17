#include "animal.hpp"
#include "simulation.hpp"

Animal::Animal(Simulation * m, int x, int y, int energie, QPixmap i) : energie(energie){
  this->monde = new Simulation;
  this->monde = m;
  this->setPos(x, y);
  this->setPixmap(i);
  taille = i.width();
}
Animal::~Animal(){}

int Animal::getEnergie(){
  return this->energie;
}

char Animal::getID() {
  return id;
}

void Animal::setEnergie(int energie){
  this->energie = energie;
}

void Animal::affiche(){
  monde->addItem(this);
}

void Animal::bouge() {
  int sens = rand() % 4;
  switch(sens) {
    case 0:
      if (this->x() > monde->borderLeft()) this->setX(this->x() - 1);
      break;
    case 1:
      if (this->x() + taille < monde->borderRight()) this->setX(this->x() + 1);
      break;
    case 2:
      if (this->y() > monde->borderTop()) this->setY(this->y() - 1);
      break;
    case 3:
      if (this->y() + taille < monde->borderBottom()) this->setY(this->y() + 1);
      break;
  }
  energie--;
  if (energie == 0) {
    this->setPixmap(monde->getImageMort());
    if(this->getID() == 'L') monde->setLion(monde->getLion() - 1);
    else if(this->getID() == 'G') monde->setGazelle(monde->getGazelle() - 1);
  }
}
