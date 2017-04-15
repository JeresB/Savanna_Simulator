#include "Animal.hpp"
#include "Monde.hpp"

int Animal::nb_animaux = 0;

// Constructeur Animal
Animal::Animal(int x_init, int y_init, int energie_init, char id_init, Monde *monde_init) {
	x = x_init;
	y = y_init;
	energie = energie_init;
	id = id_init;
	monde = monde_init;
}

// Destructeur Animal
Animal::~Animal() {}

// Methodes Animal------------------------------------------------------------------------------------------------------

// methode affiche() pour afficher les caractéristiques d'un animal
void Animal::affiche() {
	printf("x = %d, y = %d, energie = %d\n", x,y,energie);
}

// methode bouge() qui permet le déplacement des animaux
void Animal::bouge() {
	if(energie > 0) {
		int direction = rand()%4;
		if(direction == 0 && x < monde->getMAX_X()-1) {
			x++;
		} else if(direction == 1 &&  x > 0 ) {
			x--;
		} else if(direction == 2 && y < monde->getMAX_Y()-1) {
			y++;
		} else if(direction == 3 && y > 0 ) {
			y--;
		}
		energie--;
	}

	if(energie == 0 && id != monde->getID_Mange()) {
		id = monde->getID_Mort();
	}
}

// --------------------------------------------------------------------------------------------------------------------

// Getters Animal
int Animal::getX() {
	return x;
}

int Animal::getY() {
	return y;
}

int Animal::getEnergie() {
	return energie;
}

int Animal::getNbAnimaux() {
	return nb_animaux;
}

// Setters Animal
void Animal::setX(int new_x)  {
	x = new_x;
}

void Animal::setY(int new_y) {
	y = new_y;
}

void Animal::setEnergie(int new_energie) {
	energie = new_energie;
}

void Animal::setMonde(Monde* new_monde) {
	monde = new_monde;
}

void Animal::setID(char new_id) {
	id = new_id;
}
