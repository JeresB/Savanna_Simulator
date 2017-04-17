#include "animal.hpp"

class Lion : public Animal {
	private:
		char id = 'L';
	public:
		// Constructeur
		Lion(Simulation * m, int x, int y, int energie, QPixmap i);

		// Methode
		void affiche();
		char getID();
};
