#include "Animal.hpp"

class Lion : public Animal {
	private:

	public:
		// Constructeur
		Lion(int x_init, int y_init, int energie_init, Monde *monde_init);

		// Methode
		void affiche();
		char getID();
};
