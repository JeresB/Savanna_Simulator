// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Simulation.cpp                                                    ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée la simulation                                      ----- //
// -------------------------------------------------------------------------------------------- //
#include "Simulation.hpp"
#include "Gazelle.hpp"
#include "Lion.hpp"
#include "Vegetal.hpp"

// Constructeur
Simulation::Simulation(Statistiques* stats, QObject *parent) : QGraphicsScene(parent) {
  // Fenêtre de statistiques à laquelle on envoie toutes les données
  statsWindow = stats;

  // ------ On récupère la taille de l'écran ---------------------------------------------------- //
  QRect ecran = QApplication::desktop()->availableGeometry();
  tailleX = 0.5 * ecran.width();
  tailleY = 0.5 * ecran.height();
  // -------------------------------------------------------------------------------------------- //

  // ------ Définition des images QPixmap ------------------------------------------------------- //
  lion = QPixmap("lionB.png");
  gazelle = QPixmap("gazelleB.png");
  vegetal = QPixmap("plantB.png");
  gigot = QPixmap("mangerB.png");
  tombe = QPixmap("skullB.png");
  // -------------------------------------------------------------------------------------------- //

  // ------ Création de la scène ---------------------------------------------------------------- //
  terrain = new QGraphicsRectItem(0, 0, tailleX, tailleY);
  terrain->setBrush(QColor(86, 220, 38));
  this->addItem(terrain);
  // -------------------------------------------------------------------------------------------- //

  // ------ Création du timer ------------------------------------------------------------------- //
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(vitesse);
  // -------------------------------------------------------------------------------------------- //

  // Connexion entre la simulation et la fenêtre de statistiques
  connect(this, SIGNAL(signal_valeurs(int, int, int, int, int)), statsWindow, SLOT(slot_resultat_valeur(int, int, int, int, int)));

  // ------ Création de la musique -------------------------------------------------------------- //
  musique = new QSound("Le_Roi_Lion_-_L_histoire_de_la_vie.wav", this);
  musique->setLoops(QSound::Infinite);
  musique->play();
  // -------------------------------------------------------------------------------------------- //
}

// ---------------------------------------------------------------------------------------------- //
// -------- SLOTS ------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //

// Change le nombre initial d'animaux
void Simulation::slot_nb_animaux(int nb_anim) {
  nb_animaux = nb_anim;
  qDebug() << "[SLIDER] : Nombre d'animaux initialisée a" << nb_animaux << " !";
}

// Change la proportion lion / gazelle
void Simulation::slot_setProportion(int p) {
  // Vérification que la proportion est un multiple de 2
  if (p%2 == 0) proportion = p;
  else proportion = p - 1;
  qDebug() << "[SLIDER] : Proportion de gazelles " << proportion << " fois supérieure aux lions !";
}

// Change la vitesse de la simulation
void Simulation::slot_vitesse(int v) {
  // Inversion de la valeur : plus on augmente le slider vitesse, plus ça va vite
  vitesse = 1001 - v;
  timer->setInterval(vitesse);
  qDebug() << "[SLIDER] : Vitesse initialisée a " << vitesse << " millisecondes !";
}

// Change l'énergie initiales des animaux
void Simulation::slot_setEnergie(int e) {
  energie = e;
  qDebug() << "[SLIDER] : Energie initialisée a" << e << " !";
}

// Change la largeur du terrain de la simulation
void Simulation::slot_setTailleX(int x) {
  tailleX = x;
  terrain->setRect(0, 0, tailleX, tailleY);
  qDebug() << "[SLIDER] : Largeur initialisée a" << tailleX << " !";
}

// Change la hauteur du terrain de la simulation
void Simulation::slot_setTailleY(int y) {
  tailleY = y;
  terrain->setRect(0, 0, tailleX, tailleY);
  qDebug() << "[SLIDER] : Hauteur initialisée a" << tailleY << " !";
}

// Démarre / Arrête la simulation
void Simulation::slot_simulation() {
  if (simu_en_cours == false) {
    simu_en_cours = true;
    qDebug() << "[INFO] : Simulation Activée !";

    peuplement(); // On commence par peuplé le monde de la simulation
  } else {
    simu_en_cours = false;
    qDebug() << "[INFO] : Arrêt de la simulation !";

    terminer(); // Efface les images et le vecteur d'animaux puis réinitialise les données
  }
}
// ---------------------------------------------------------------------------------------------- //
// -------- FIN DES SLOTS ----------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------- //
// -------- METHODES ---------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //

// Fonction appelée lors de l'arrêt de la simulation
// Réinitialise les images, les animaux et les données
void Simulation::terminer() {
  // Effacement de toutes les images
  for (int i = 0; i < vect_animaux.size(); i++) {
    this->removeItem(vect_animaux[i]);
  }

  // Effacement totale du vecteur d'animaux
  vect_animaux.clear();

  // Réinitialisation des données
  animaux_mort = 0;
  lion_vivant = 0;
  gazelle_vivante = 0;
  gazelle_mange = 0;
  vegetal_vivant = 0;
  emit signal_valeurs(0, 0, 0, 0, 0);
}

// Fonction appelée lors du démarrage de la simulation
// Création des animaux
void Simulation::peuplement() {
  srand(time(NULL));
  for (int i = 0; i < nb_animaux * 1.2; i++){
    // Les animaux seront placés aléatoirement dans le terrain de la simulation
    int x = rand() % (this->borderRight() - lion.width()) + this->borderLeft();
    int y = rand() % (this->borderBottom() - lion.width()) + this->borderTop();

    // Création d'une marge pour l'énergie des animaux
    // A partir de l'énergie donnée par l'utilisateur
    // Les animaux auront une énergie compris entre [0.75 * energie ; 1.25 * energie]
    if(i%2) energie += rand() % (energie / 4);
    else energie -= rand() % (energie / 4);

    // On rajoute 20% de plantes par rapport aux nombres initiales d'animaux
    if (i < nb_animaux * 0.2) {
      vect_animaux << new Vegetal(this, x, y, 0, vegetal);
      vegetal_vivant++;
    } else {
      // En fonctant de la proportion on ajoute moins de lions et donc plus de gazelles
      if (i%proportion == 0) {
        vect_animaux << new Lion(this, x, y, energie, lion);
        lion_vivant++;
      } else {
        vect_animaux << new Gazelle(this, x, y, energie, gazelle);
        gazelle_vivante++;
      }
    }

    // Enfin : on ajout l'image de l'animal à la simulation
    this->addItem(vect_animaux.last());
  }
}

// Si les lions rencontrent des gazelles
// Ou des gazelles qui croisent des plantes
void Simulation::affrontement(int animal) {
  // Pour tous les animaux
  for (int i = 0; i < vect_animaux.size(); i++) {
    // Si un lion rencontre une gazelle
    if (vect_animaux[animal]->getID() == 'L' && vect_animaux[i]->getID() == 'G' && vect_animaux[animal]->collidesWithItem(vect_animaux[i])) {
      // Le lion récupère l'énergie de la gazelle
      vect_animaux[animal]->setEnergie(vect_animaux[animal]->getEnergie() + vect_animaux[i]->getEnergie());
      // Si l'énergie du lion dépasse l'énergie initiale de plus de 50%
      // Alors on crée un nouveau lion
      if(vect_animaux[animal]->getEnergie() > energie * 1.5) {
        naissance(vect_animaux[animal]->getID());
      }
      // La gazelle n'a plus d'énergie
      vect_animaux[i]->setEnergie(0);
      // On modifie l'image de la gazelle à : "Manger"
      vect_animaux[i]->setPixmap(gigot);
      // L'id de la gazelle de M pour manger
      vect_animaux[i]->setID('M');

      // Actualisation des données
      gazelle_vivante--;
      gazelle_mange++;
      animaux_mort++;

    // Si une gazelle rencontre une plante
    } else if (vect_animaux[animal]->getID() == 'G' && vect_animaux[i]->getID() == 'V' && vect_animaux[animal]->collidesWithItem(vect_animaux[i])) {
      // Si la gazelle mange une plante alors son énergie est doublée
      vect_animaux[animal]->setEnergie(vect_animaux[animal]->getEnergie() * 2);
      // Si l'énergie de la gazelle dépasse l'énergie initiale de plus de 50%
      // Alors on crée une nouvelle gazelle
      if(vect_animaux[animal]->getEnergie() > energie * 1.5) {
        naissance(vect_animaux[animal]->getID());
      }
      // On supprime l'image de la plante de notre simulation
      this->removeItem(vect_animaux[i]);
      // On supprime la plante du vecteur
      vect_animaux.removeAt(i);
      // Actualisation des données
      vegetal_vivant--;
    }
  }
}

// Fonction appelée à la naissance d'un nouvel animal
void Simulation::naissance(char type) {
  // Variable x, y, energie nécessaire à la création d'un animal --------------------------------- //
  int x = rand() % (this->borderRight() - lion.width()) + this->borderLeft();
  int y = rand() % (this->borderBottom() - lion.width()) + this->borderTop();
  if(rand()%2) energie += rand() % (energie / 4);
  else energie -= rand() % (energie / 4);
  // --------------------------------------------------------------------------------------------- //

  // Création d'un animal en fonction de ses parents
  if (type == 'G') {
    vect_animaux << new Gazelle(this, x, y, energie, gazelle);
    gazelle_vivante++;
  } else if (type == 'L') {
    vect_animaux << new Lion(this, x, y, energie, lion);
    lion_vivant++;
  }
  // Ajout du nouvelle animal au monde pour qu'on puisse le voir
  this->addItem(vect_animaux.last());
}

// Fonction qui calcul la distance la plus petite
// Indique le sens le plus intelligent
// Si le sens vaut -1 alors le déplacement sera aléatoire
int Simulation::plus_proche(int a) {
  int distance = 9999;
  int d = 0;
  int indice = -1;
  int sens = -1;

  // On veut déplacer un lion
  if (vect_animaux[a]->getID() == 'L') {
    // On cherche donc une gazelle
    for (int i = 0; i < vect_animaux.size(); i++) {
      // Si une gazelle à été trouvée
      if (vect_animaux[i]->getID() == 'G') {
        // On calcul la distance entre le lion et la gazelle
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));

        // Si la distance est plus petite que la plus petite distance enregistrer
        if (d < distance) {
          // On enrengistre la distance la plus petite
          distance = d;
          // On sauvegarde l'indice vers la gazelle la plus proche
          indice = i;
        }
      }
    }
    // On appel la fonction déplacement intelligent pour trouver le bon sens
    sens = deplacement_intelligent(a, indice);
  // On déplace une gazelle
  } else if (vect_animaux[a]->getID() == 'G') {
    // On cherche une plante ou un lion
    for (int i = 0; i < vect_animaux.size(); i++) {
      // Si une plante à été trouvée
      if (vect_animaux[i]->getID() == 'V') {
        // On calcul la distance entre la gazelle et la plante
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));

        // Si la distance est plus petite que la plus petite distance enregistrer
        if (d < distance) {
          // On enrengistre la distance la plus petite
          distance = d;
          // On sauvegarde l'indice vers la plante la plus proche
          indice = i;
        }
      // Si un lion à été trouvé
      } else if (vect_animaux[i]->getID() == 'L') {
        // On calcul la distance entre la gazelle et le lion
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));

        // Si la distance est plus petite que la plus petite distance enregistrer
        if (d < distance) {
          // On enrengistre la distance la plus petite
          distance = d;
          // On sauvegarde l'indice vers le lion le plus proche
          indice = i;
        }
      }
    }
    // On appel la fonction déplacement intelligent pour trouver le bon sens
    sens = deplacement_intelligent(a, indice);
  }
  // On retourne le sens le plus intelligent
  return sens;
}

// Fonction qui choisi le meilleur sens pour le déplacemen intelligent
int Simulation::deplacement_intelligent(int a1, int a2) {
  int sens = -1; // -1 : aléatoire

  // Si a2 vaut moins il n'y a aucun déplacement intelligent à faire
  // Exemple : plus aucune gazelle
  if (a2 != -1) {
    // Il a 2 directions possibles pour se déplacer vers un point
    // On en choisi un aléatoirement
    if(rand()%2 == 0) {
      // Choix du meilleur sens en fonction des positions des 2 animaux
      if (vect_animaux[a1]->x() > vect_animaux[a2]->x()) {
        // Si a1 : gazelle et a2 : lion, alors on éloigne la gazelle
        if(vect_animaux[a2]->getID() == 'L') sens = 1;
        sens = 0;
      } else if (vect_animaux[a1]->x() < vect_animaux[a2]->x()) {
        if(vect_animaux[a2]->getID() == 'L') sens = 0;
        sens = 1;
      }
    } else {
      if (vect_animaux[a1]->y() > vect_animaux[a2]->y()) {
        if(vect_animaux[a2]->getID() == 'L') sens = 3;
        sens = 2;
      } else if (vect_animaux[a1]->y() < vect_animaux[a2]->y()) {
        if(vect_animaux[a2]->getID() == 'L') sens = 2;
        sens = 3;
      }
    }
  }

  // On retourne le sens
  return sens;
}

// Fonction principale de la simulation, équivalente à "PasseUnTour()"
void Simulation::update() {
  // Si la simulation est en cours ...
  if (simu_en_cours == true) {
    // Pour tous les animaux et plantes
    for (int i = 0; i < vect_animaux.size(); i++) {
      // Si l'énergie est supérieure à 0 (animal vivant)
      if (vect_animaux[i]->getEnergie() > 0) {
        // Si c'est une plante
        if (vect_animaux[i]->getID() == 'V') {
          // On appel la méthode nature qui permet de faire évoluer la nature
          nature(i);
        } else {
          // On cherche un sens intelligent
          sens = plus_proche(i);
          // Déplacement de l'animal avec un sens intelligent
          vect_animaux[i]->bouge(sens);
          // Si les lions rencontrent des gazelles ou que des gazelles rencontrent des plantes
          affrontement(i);
        }
      }
    }

    // On envoie toutes les données à afficher
    emit signal_valeurs(lion_vivant, gazelle_vivante, animaux_mort, gazelle_mange, vegetal_vivant);
  }
}

// Fonction qui permet de faire pousser les plantes aléatoirement
void Simulation::nature(int i) {
  bool ajout_OK = false; // Pour savoir si une nouvelle plante à été crée
  nature_naissance++; // Agis comme compteur pour éviter que la nature prenne le contrôle
  if (nature_naissance >= FREQUENCE_NATURE && vegetal_vivant < MAX_VEGETAUX) {

    nature_naissance = 0;
    int direction = rand() % 4; // Direction aléatoire

    // Direction vers laquelle une nouvelle plantes va naître
    // On ajout une plante si elle est dans le tarrain de la simulation
    switch (direction) {
      case 0:
      if(vect_animaux[i]->x() + 32 < borderBottom()) {
        vect_animaux << new Vegetal(this, vect_animaux[i]->x() + 32, vect_animaux[i]->y(), 0, vegetal);
        ajout_OK = true;
      }
      break;
      case 1:
      if(vect_animaux[i]->x() - 32 > borderTop()) {
        vect_animaux << new Vegetal(this, vect_animaux[i]->x() - 32, vect_animaux[i]->y(), 0, vegetal);
        ajout_OK = true;
      }
      break;
      case 2:
      if(vect_animaux[i]->y() + 32 < borderRight()) {
        vect_animaux << new Vegetal(this, vect_animaux[i]->x(), vect_animaux[i]->y() + 32, 0, vegetal);
        ajout_OK = true;
      }
      break;
      case 3:
      if(vect_animaux[i]->y() - 32 > borderLeft()) {
        vect_animaux << new Vegetal(this, vect_animaux[i]->x(), vect_animaux[i]->y() - 32, 0, vegetal);
        ajout_OK = true;
      }
      break;
    }

    // Si la nouvelle plante est naît : on l'ajout au terrain de la simulation
    if(ajout_OK == true) {
      this->addItem(vect_animaux.last());
      vegetal_vivant++;
    }
  }
}

// ---------------------------------------------------------------------------------------------- //
// -------- GETTERS ----------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
QPixmap Simulation::getImageMort() {
  return tombe;
}

int Simulation::getLion() {
  return lion_vivant;
}

int Simulation::getGazelle() {
  return gazelle_vivante;
}

int Simulation::getMort() {
  return animaux_mort;
}
// ---------------------------------------------------------------------------------------------- //
// -------- FIN DES GETTERS --------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------- //
// -------- SETTERS ----------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
void Simulation::setLion(int l) {
  lion_vivant = l;
}

void Simulation::setGazelle(int g) {
  gazelle_vivante = g;
}

void Simulation::setMort(int m) {
  animaux_mort = m;
}
// ---------------------------------------------------------------------------------------------- //
// -------- FIN DES SETTERS --------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------- //
// -------- GETTERS : bordures de la simulation ------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
int Simulation::borderLeft() {
  QRectF r = terrain->rect();
  return r.left();
}

int Simulation::borderRight() {
  QRectF r = terrain->rect();
  return r.right();
}

int Simulation::borderTop() {
  QRectF r = terrain->rect();
  return r.top();
}

int Simulation::borderBottom() {
  QRectF r = terrain->rect();
  return r.bottom();
}
// ---------------------------------------------------------------------------------------------- //
// -------- FIN DES GETTERS : bordures de la simulation ----------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
