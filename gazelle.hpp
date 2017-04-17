#include "animal.hpp"

class Gazelle : public Animal {
	private:
		char id = 'G';
	public:
		// Constructeur
		Gazelle(Simulation * m, int x, int y, int energie, QPixmap i);

		// Methode
		void affiche();
		char getID();
};
