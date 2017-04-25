#include "Vegetal.hpp"
#include "Simulation.hpp"

Vegetal::Vegetal(Simulation * m, int x, int y, int energie, QPixmap i) : Animal(m, x, y, energie, i) {};

char Vegetal::getID() {
  return id;
}

void Vegetal::setID(char id_set) {
  id = id_set;
}
