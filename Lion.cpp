#include "Lion.hpp"
#include "Monde.hpp"

Lion::Lion(int x_init, int y_init, int energie_init, Monde *monde_init)
: Animal(x_init, y_init, energie_init, Monde::getID_Lion(), monde_init) {};

void Lion::affiche() {
	printf("Lion : x = %d, y = %d, energie = %d, id = %c\n", x,y,energie,id);
}

char Lion::getID() {
	return id;
}
