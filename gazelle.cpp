#include "gazelle.hpp"
#include "simulation.hpp"

Gazelle::Gazelle(Simulation * m, int x, int y, int energie, QPixmap i)
 : Animal(m, x, y, energie, i) {
   id = 'G';
 };

void Gazelle::affiche() {
  qDebug() << "Gazelle";
}

char Gazelle::getID() {
  return id;
}
