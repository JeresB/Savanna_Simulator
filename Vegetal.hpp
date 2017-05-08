// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Vegetal.hpp                                                       ----- //
// ----- Type         : header	                                                         	----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une Plante                                        	----- //
// -------------------------------------------------------------------------------------------- //
#include "Animal.hpp"

class Vegetal : public Animal {
	private:
		char id = 'V'; // identifiant de la plante

	public:
		// Constructeur et destructeur
		Vegetal(Simulation * m, int x, int y, int energie, QPixmap i);
		~Vegetal(){};

		// Getter
		char getID();
		// Setter
		void setID(char id_set);
};
