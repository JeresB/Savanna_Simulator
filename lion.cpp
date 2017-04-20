#include "lion.hpp"
#include "simulation.hpp"

Lion::Lion(Simulation * m, int x, int y, int energie, QPixmap i)
 : Animal(m, x, y, energie, i) {
   id = 'L';
 };

void Lion::affiche() {
  qDebug() << "Lion";
}

char Lion::getID() {
  return id;
}

void Lion::setID(char id_set) {
  id = id_set;
}
