#include "Monde.hpp"
#include "Gazelle.hpp"
#include "Lion.hpp"
#include "Animal.hpp"
#include <vector>

// Constructeur Monde
Monde::Monde(int nb_animaux_init, int x, int y) {
	max_x = x;
	max_y = y;
	nb_animaux = nb_animaux_init;

	tab2D = new char* [max_y];
	for ( int i=0 ; i < max_y ; i++)
	tab2D[i] = new char [max_x];

	for(int i = 0; i < max_y; i++) {
		for(int j = 0; j < max_x; j++) {
			tab2D[i][j] = ' ';
		}
	}

	Peuplement();
	affiche_carte();
}

// Destructeur Monde
Monde::~Monde() {}

// Methodes Monde ----------------------------------------------------------------------------------------------------------

// methode peuplement() qui initialise le monde de départ
void Monde::Peuplement() {
	int x,y,e;

	for(int i = 0; i < nb_animaux;i++) {
		x = rand()%max_x;
		y = rand()%max_y;
		e = rand()%100+1;

		if( i%2 == 0) {
			vect_anim.push_back(new Lion(x, y, e, this));
		} else {
			vect_anim.push_back(new Gazelle(x, y, e, this));
		}
		tab2D[y][x] = vect_anim[i]->getID();
	}
}

// methode affiche() qui affiche la carte du monde tab2D
void Monde::affiche_carte() {
	printf("--------------------------------------------------\n\n");

	for(int i=0; i<max_y; i++) {
		for(int j=0; j<max_x; j++) {
			std::cout << tab2D[i][j];
		}
		std::cout << std::endl;
	}
	printf("--------------------------------------------------\n\n");
}

// methode update() qui met à jour la carte du monde tab2D
void Monde::update(int x, int y, char c, int pos) {
	if(tab2D[y][x] == id_gazelle && vect_anim[pos]->getID() == id_lion) {
		for(int i=0; i<nb_animaux; i++) {
			if (vect_anim[i]->getX() == x && vect_anim[i]->getY() == y && vect_anim[i]->getID() == id_gazelle) {
				vect_anim[i]->setEnergie(0);
				vect_anim[i]->setID(id_mange);
				nb_mange++;
			}
		}
	} else if(tab2D[y][x] == id_lion && vect_anim[pos]->getID() == id_gazelle) {
		vect_anim[pos]->setEnergie(0);
		vect_anim[pos]->setID(id_mange);
		nb_mange++;
	}
	tab2D[y][x] = c;
}

// methode passeuntour() qui met en mouvement les animaux dans la carte du monde tab2D
void Monde::passeuntour() {
	//while(nb_mort < nb_animaux) {
		nb_mort = 0;
		system("clear");
		for(int i = 0; i < nb_animaux; i++) {
			if(vect_anim[i]->getEnergie() > 0) {
				update(vect_anim[i]->getX(), vect_anim[i]->getY(),' ',i);
				vect_anim[i]->bouge();
				update(vect_anim[i]->getX(),vect_anim[i]->getY(), vect_anim[i]->getID(),i);
			} else {
				update(vect_anim[i]->getX(), vect_anim[i]->getY(), vect_anim[i]->getID(),i);
				nb_mort++;
			}
		}
		affiche_carte();
		usleep(200000);
	//}
	//printf("Les lions ont mangé %d gazelles\n\n",nb_mange);
}

// ----------------------------------------------------------------------------------------------------------------------------------

// Getters
int Monde::getMAX_X() {
	return max_x;
}

int Monde::getMAX_Y() {
	return max_y;
}

int Monde::getNbAnimaux() {
	return nb_animaux;
}

int Monde::getNbMort() {
	return nb_mort;
}

char Monde::getElementTab2D(int i, int j) {
	return tab2D[i][j];
}

std::vector<Animal*> Monde::getVect() {
	return vect_anim;
}

char Monde::getID_Lion() {
	return id_lion;
}

char Monde::getID_Gazelle() {
	return id_gazelle;
}

char Monde::getID_Mort() {
	return id_mort;
}

char Monde::getID_Mange() {
	return id_mange;
}
