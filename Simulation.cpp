#include "Simulation.hpp"
#include "Gazelle.hpp"
#include "Lion.hpp"
#include "Vegetal.hpp"

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
  for (int i = 0; i < vect_animaux.size(); i++) {
    if (vect_animaux[animal]->getID() == 'L') {
      if(vect_animaux[animal]->collidesWithItem(vect_animaux[i])) {
        if (vect_animaux[i]->getID() == 'G') {
          vect_animaux[animal]->setEnergie(vect_animaux[animal]->getEnergie() + vect_animaux[i]->getEnergie());
          vect_animaux[i]->setEnergie(0);
          vect_animaux[i]->setPixmap(gigot);
          vect_animaux[i]->setID('M');
          gazelle_vivante--;
          gazelle_mange++;
          animaux_mort++;
        }
      }
    } else if (vect_animaux[animal]->getID() == 'G') {
      if(vect_animaux[animal]->collidesWithItem(vect_animaux[i])) {
        if (vect_animaux[i]->getID() == 'V') {
          vect_animaux[animal]->setEnergie(vect_animaux[animal]->getEnergie() * 2);
          this->removeItem(vect_animaux[i]);
          vect_animaux[i]->setID('X');
          vegetal_vivant--;
        }
      }
    }
  }
}

int Simulation::plus_proche(int a) {
  int distance = 9999;
  int d = 0;
  int indice = -1;
  int sens = -1;
  if (vect_animaux[a]->getID() == 'L') {
    for (int i = 0; i < vect_animaux.size(); i++) {
      if (vect_animaux[i]->getID() == 'G') {
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));
        if (d < distance) {
          distance = d;
          indice = i;
        }
      }
    }
    sens = deplacement_intelligent(a, indice);
  } else if (vect_animaux[a]->getID() == 'G') {
    for (int i = 0; i < vect_animaux.size(); i++) {
      if (vect_animaux[i]->getID() == 'V') {
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));
        if (d < distance) {
          distance = d;
          indice = i;
        }
      }
    }
    sens = deplacement_intelligent(a, indice);
  } else if (vect_animaux[a]->getID() == 'G') {
    for (int i = 0; i < vect_animaux.size(); i++) {
      if (vect_animaux[i]->getID() == 'L') {
        d = sqrt(pow(vect_animaux[i]->x() - vect_animaux[a]->x(), 2) + pow(vect_animaux[i]->y() - vect_animaux[a]->y(), 2));
        if (d < distance) {
          distance = d;
          indice = i;
        }
      }
    }
    sens = deplacement_intelligent(a, indice);
  }
  return sens;
}

int Simulation::deplacement_intelligent(int a1, int a2) {
  int sens = -1;
  if (a2 != -1) {
    if(rand()%2 == 0) {
      if (vect_animaux[a1]->x() > vect_animaux[a2]->x()) {
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
        // On cherche un sens intelligent
        sens = plus_proche(i);
        // Déplacement de l'animal avec un sens intelligent
        vect_animaux[i]->bouge(sens);
        // Si les lions rencontrent des gazelles ou que des gazelles rencontrent des plantes
        affrontement(i);
      }
      // Si c'est une plante
      if (vect_animaux[i]->getID() == 'V') {
        // On appel la méthode nature qui permet de faire évoluer la nature
        nature(i);
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
  if (nature_naissance >= FREQUENCE_NATURE && lion_vivant > 0 ) {

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
