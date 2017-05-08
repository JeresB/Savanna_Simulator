// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Vegetal.cpp                                                       ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une Plante                                         ----- //
// -------------------------------------------------------------------------------------------- //
#include "Vegetal.hpp"
#include "Simulation.hpp"

// Constructeur
Vegetal::Vegetal(Simulation * m, int x, int y, int energie, QPixmap i) : Animal(m, x, y, energie, i) {}

// Getter ID
char Vegetal::getID() {
  return id;
}

// Setter ID
void Vegetal::setID(char id_set) {
  id = id_set;
}
