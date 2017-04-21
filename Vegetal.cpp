#include "Vegetal.hpp"
#include "simulation.hpp"

Vegetal::Vegetal(Simulation * m, int x, int y, int energie, QPixmap i)
 : Animal(m, x, y, 0, i) {
   id = 'G';
 };

void Vegetal::affiche() {
  qDebug() << "Vegetal";
}

char Vegetal::getID() {
  return id;
}

void Vegetal::setID(char id_set) {
  id = id_set;
}
