#include "Animal.hpp"

class Lion : public Animal {
	private:
		char id = 'L';

	public:
		// Constructeur
		Lion(Simulation * m, int x, int y, int energie, QPixmap i);
		~Lion(){};

		// Methode
		char getID();
		void setID(char id_set);
};
