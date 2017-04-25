#include "Animal.hpp"

class Vegetal : public Animal {
	private:
		char id = 'V';

	public:
		// Constructeur
		Vegetal(Simulation * m, int x, int y, int energie, QPixmap i);
		~Vegetal(){};

		// Methode
		char getID();
		void setID(char id_set);
};
