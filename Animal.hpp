#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>

class Monde;
class Animal {
	protected:
		// Attributs

		int x;
		int y;
		int energie;
		char id;
		static int nb_animaux;
		Monde* monde;

	public:
		// Constructeur
		Animal(int x, int y, int energie, char id, Monde *monde);

		// Destructeur
		~Animal();

		// Methodes
		virtual void affiche();
		void bouge();

		// Getters
		int getX();
		int getY();
		int getEnergie();
		virtual char getID() = 0;
		static int getNbAnimaux();

		// Setters
		void setX(int x);
		void setY(int y);
		void setEnergie(int energie);
		void setMonde(Monde* monde);
		void setID(char id);
};

#endif
