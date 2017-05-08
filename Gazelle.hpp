// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Gazelle.hpp                                                       ----- //
// ----- Type         : header	                                                         	----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une Gazelle                                        ----- //
// -------------------------------------------------------------------------------------------- //
#include "Animal.hpp"

class Gazelle : public Animal {
	private:
		char id = 'G'; // identifiant de la gazelle

	public:
		// Constructeur et destructeur
		Gazelle(Simulation * m, int x, int y, int energie, QPixmap i);
		~Gazelle(){};

		// Getter
		char getID();
		// Setter
		void setID(char id_set);
};
