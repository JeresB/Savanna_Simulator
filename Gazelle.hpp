#include "Animal.hpp"

class Gazelle : public Animal {
	private:

	public:
		// Constructeur
		Gazelle(int x_init, int y_init, int energie_init, Monde *monde_init);

		// Methode
		void affiche();
		char getID();
};
