// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Lion.cpp                                                          ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée un Lion                                            ----- //
// -------------------------------------------------------------------------------------------- //
#include "Lion.hpp"
#include "Simulation.hpp"

// Constructeur
Lion::Lion(Simulation * m, int x, int y, int energie, QPixmap i) : Animal(m, x, y, energie, i) {}

// Getter ID
char Lion::getID() {
  return id;
}

// Setter ID
void Lion::setID(char id_set) {
  id = id_set;
}
