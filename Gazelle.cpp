// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Gazelle.cpp                                                       ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une Gazelle                                        ----- //
// -------------------------------------------------------------------------------------------- //
#include "Gazelle.hpp"
#include "Simulation.hpp"

// Constructeur
Gazelle::Gazelle(Simulation * m, int x, int y, int energie, QPixmap i) : Animal(m, x, y, energie, i) {}

// Getter ID
char Gazelle::getID() {
  return id;
}

// Setter ID
void Gazelle::setID(char id_set) {
  id = id_set;
}
