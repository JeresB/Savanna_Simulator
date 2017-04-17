#include "simulation.hpp"

Simulation::Simulation(QObject *parent) : QGraphicsScene(parent) {
  //qRegisterMetaType<QVector<Animal*> >("QVector<Animal*>");

  QRect ecran = QApplication::desktop()->availableGeometry();
  hauteur = ecran.height();
  largeur = ecran.width();

  tailleX = largeur * 0.5;
  tailleY = hauteur * 0.5;

  lion = QPixmap("lion.png");
  //gazelle = QPixmap("gazelle2.png");
  //gigot = QPixmap("mange.png");
  //tombe = QPixmap("rip.png");

  terrain = new QGraphicsRectItem(0, 0, tailleX, tailleY);
  terrain->setBrush(QColor(15, 72, 242));
  this->addItem(terrain);

  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);
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

void Simulation::slot_simulation_animal() {
  if (simu_en_cours == false) {
    //fonction demarrer la simulation
    peuplement();
    //leopard = new Animal(this, 0, 0, 100, lion);
    //QGraphicsPixmapItem* leo = new QGraphicsPixmapItem(lion);
    //leo->setPos(100, 100);
    //this->addItem(leopard);
    sens = 10;

    simu_en_cours = true;
  } else {
    //fonction effacer la liste d'animaux;
    simu_en_cours = false;
  }
}

void Simulation::peuplement() {
  srand(time(NULL));
  for (int i = 0; i < nb_animaux; i++){
    int x = rand() % this->borderRight() + this->borderLeft();
    int y = rand() % this->borderBottom() + this->borderTop();
    if (x >= this->borderRight()) x = x - lion.width();
    if (y >= this->borderBottom()) y = y - lion.width();
    int e = rand() % 100;
    tab_anim << new Animal(this, x, y, e, lion);
    this->addItem(tab_anim.last());
  }
}

void Simulation::update() {
  if (simu_en_cours == true) {
    //this->removeItem(leopard);
    //leopard->bouge();
    for (int i = 0; i < nb_animaux; i++) {
      if (tab_anim[i]->getEnergie() > 0) {
        tab_anim[i]->bouge();
      }

    }
    //this->addItem(leopard);
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
