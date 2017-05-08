// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Lion.hpp                                                       		----- //
// ----- Type         : header	                                                         	----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée un Lion                                        		----- //
// -------------------------------------------------------------------------------------------- //
#include "Animal.hpp"

class Lion : public Animal {
	private:
		char id = 'L'; // identifiant du lion

	public:
		// Constructeur et destructeur
		Lion(Simulation * m, int x, int y, int energie, QPixmap i);
		~Lion(){};

		// Getter
		char getID();
		// Setter
		void setID(char id_set);
};
