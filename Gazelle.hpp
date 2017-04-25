#include "Animal.hpp"

class Gazelle : public Animal {
	private:
		char id = 'G';

	public:
		// Constructeur
		Gazelle(Simulation * m, int x, int y, int energie, QPixmap i);
		~Gazelle(){};

		// Methode
		char getID();
		void setID(char id_set);
};
