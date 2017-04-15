#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include "Animal.hpp"
#include <vector>
#include <string>
#include <QApplication>
#include <QObject>

class Monde : public QObject {
	Q_OBJECT
	private:
	// Attributs ----------------------------------------------------------------------------------------------------------------

		int nb_animaux; // nombre d'animaux

		// Taille du monde
		static const int MAX_X = 50;
		static const int MAX_Y = 20;
		int max_x = 50, max_y = 20;

		//char tab2D[MAX_Y][MAX_X]; // Carte du monde
		char **tab2D;

		//Animal** tab_animaux = NULL; // Tableau d'animaux
		std::vector<Animal*> vect_anim; // Vecteur d'animaux

		int nb_mange = 0; // Nombre de gazelles manger par les lions
		int nb_mort = 0;

		// Identification des animaux dans la carte du monde
		static const char id_lion = 'L';
		static const char id_gazelle = 'G';
		static const char id_mort = 'X';
		static const char id_mange = 'M';

		// ---------------------------------------------------------------------------------------------------------------------------
	public:
		// Constructeur
		Monde(int nb_animaux, int x, int y);

		// Destructeur
		~Monde();

		// Methodes
		void Peuplement();
		void passeuntour();
		void affiche_carte();
		void update(int x, int y, char c, int pos);

		// Getters
		int getMAX_X();
		int getMAX_Y();


		int getNbAnimaux();
		int getNbMort();

		char getElementTab2D(int i, int j);
		std::vector<Animal*> getVect();

		static char getID_Lion();
		static char getID_Gazelle();
		static char getID_Mort();
		static char getID_Mange();
};
