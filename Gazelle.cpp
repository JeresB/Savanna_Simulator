#include "Gazelle.hpp"
#include "Simulation.hpp"

Gazelle::Gazelle(Simulation * m, int x, int y, int energie, QPixmap i) : Animal(m, x, y, energie, i) {};

char Gazelle::getID() {
  return id;
}

void Gazelle::setID(char id_set) {
  id = id_set;
}
