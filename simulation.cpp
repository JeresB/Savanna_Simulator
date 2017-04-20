#include "simulation.hpp"
#include "gazelle.hpp"
#include "lion.hpp"

Simulation::Simulation(QObject *parent) : QGraphicsScene(parent) {
  //qRegisterMetaType<QVector<Animal*> >("QVector<Animal*>");

  QRect ecran = QApplication::desktop()->availableGeometry();
  hauteur = ecran.height();
  largeur = ecran.width();

  tailleX = largeur * 0.5;
  tailleY = hauteur * 0.5;

  lion = QPixmap("lion.png");
  gazelle = QPixmap("gazelle2.png");
  gigot = QPixmap("mange.png");
  tombe = QPixmap("rip.png");

  terrain = new QGraphicsRectItem(0, 0, tailleX, tailleY);
  terrain->setBrush(QColor(15, 72, 242));
  this->addItem(terrain);

  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(vitesse);
}

Simulation::~Simulation() {}

void Simulation::slot_setTailleX(int x) {
  tailleX = x;
  terrain->setRect(0, 0, tailleX, tailleY);
}

void Simulation::slot_setTailleY(int y) {
  tailleY = y;
  terrain->setRect(0, 0, tailleX, tailleY);
}

void Simulation::slot_setProportion(int p) {
  if (p%2 == 0) {
    proportion = p;
  } else {
    proportion = p - 1;
  }

}

void Simulation::slot_vitesse(int v) {
  vitesse = 201 - v;
  timer->stop();
  timer->start(vitesse);
}

void Simulation::slot_setEnergie(int e) {
  energie = e;
}

void Simulation::slot_simulation_animal(Statistiques* &statsWindow) {
  if (simu_en_cours == false) {
    //fonction demarrer la simulation
    connect(this, SIGNAL(signal_valeurs(int, int, int, int)), statsWindow, SLOT(slot_resultat_valeur(int, int, int, int)));
    temps = 0;
    temps_simulation.restart();
    peuplement();
    //leopard = new Animal(this, 0, 0, 100, lion);
    //QGraphicsPixmapItem* leo = new QGraphicsPixmapItem(lion);
    //leo->setPos(100, 100);
    //this->addItem(leopard);
    sens = 10;

    simu_en_cours = true;
  } else {
    //fonction effacer la liste d'animaux;
    terminer();
    simu_en_cours = false;
    temps = temps_simulation.elapsed();
  }
}

void Simulation::peuplement() {
  srand(time(NULL));
  for (int i = 0; i < nb_animaux; i++){
    int x = rand() % this->borderRight() + this->borderLeft();
    int y = rand() % this->borderBottom() + this->borderTop();
    if (x >= this->borderRight()) x = x - lion.width();
    if (y >= this->borderBottom()) y = y - lion.width();

    if (i%proportion == 0) {
      tab_anim << new Lion(this, x, y, energie, lion);
      lion_vivant++;
    } else {
      tab_anim << new Gazelle(this, x, y, energie, gazelle);
      gazelle_vivante++;
    }

    this->addItem(tab_anim.last());
  }
}

void Simulation::affrontement(int animal) {
  for (int i = 0; i < tab_anim.size(); i++) {
    if (tab_anim[animal]->getID() == 'L') {
      if(tab_anim[animal]->collidesWithItem(tab_anim[i])) {
        if (tab_anim[i]->getID() == 'G') {
          tab_anim[animal]->setEnergie(tab_anim[animal]->getEnergie() + tab_anim[i]->getEnergie());
          tab_anim[i]->setEnergie(0);
          tab_anim[i]->setPixmap(gigot);
          tab_anim[i]->setID('M');
          gazelle_vivante--;
          gazelle_mange++;
        }
      }
    } else if (tab_anim[animal]->getID() == 'G') {
      if(tab_anim[animal]->collidesWithItem(tab_anim[i])) {
        if (tab_anim[i]->getID() == 'L') {
          tab_anim[i]->setEnergie(tab_anim[i]->getEnergie() + tab_anim[animal]->getEnergie());
          tab_anim[animal]->setEnergie(0);
          tab_anim[animal]->setPixmap(gigot);
          tab_anim[animal]->setID('M');
          gazelle_vivante--;
          gazelle_mange++;
        }
      }
    }
  }
}

void Simulation::terminer() {
  for (int i = 0; i < tab_anim.size(); i++) {
    this->removeItem(tab_anim[i]);
  }
}

void Simulation::update() {
  if (simu_en_cours == true) {
    //this->removeItem(leopard);
    //leopard->bouge();
    for (int i = 0; i < nb_animaux; i++) {
      if (tab_anim[i]->getEnergie() > 0) {
        affrontement(i);
        tab_anim[i]->bouge();
      }

    }
    emit signal_valeurs(lion_vivant, gazelle_vivante, animaux_mort, gazelle_mange);
  }
}

void Simulation::slot_nb_animaux(int nb_anim) {
  nb_animaux = nb_anim;
}

int Simulation::getMAX_X() {
  return tailleX;
}

int Simulation::getMAX_Y() {
  return tailleY;
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

QPixmap Simulation::getImageMort() {
  return tombe;
}

void Simulation::setLion(int l) {
  lion_vivant = l;
}

void Simulation::setGazelle(int g) {
  gazelle_vivante = g;
}

void Simulation::setMort(int m) {
  animaux_mort = m;
}

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
