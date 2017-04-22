#include "Vegetal.hpp"
#include "simulation.hpp"

Vegetal::Vegetal(Simulation * m, int x, int y, int energie, QPixmap i)
 : Animal(m, x, y, energie, i) {
   id = 'V';
   nature_naissance = 0;
};

void Vegetal::affiche() {
  qDebug() << "Vegetal";
}

char Vegetal::getID() {
  return id;
}

int Vegetal::getNature() {
  return nature_naissance;
}

void Vegetal::setID(char id_set) {
  id = id_set;
}

void Vegetal::setNature(int n) {
  nature_naissance = n;
}
