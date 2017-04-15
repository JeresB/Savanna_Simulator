#include "Gazelle.hpp"
#include "Monde.hpp"

Gazelle::Gazelle(int x_init, int y_init, int energie_init, Monde *monde_init)
: Animal(x_init, y_init, energie_init, Monde::getID_Gazelle(), monde_init) {};

void Gazelle::affiche() {
	printf("Gazelle : x = %d, y = %d, energie = %d, id = %c\n", x,y,energie,id);
}

char Gazelle::getID() {
	return id;
}
