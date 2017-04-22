#include "animal.hpp"

class Vegetal : public Animal {
	private:
		char id = 'V';
		int nature_naissance;
	public:
		// Constructeur
		Vegetal(Simulation * m, int x, int y, int energie, QPixmap i);

		// Methode
		void affiche();
		char getID();
		int getNature();
		void setID(char id_set);
		void setNature(int n);
};
