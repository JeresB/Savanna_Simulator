#include "simulation.hpp"

Simulation::Simulation(QObject *parent) : QGraphicsScene(parent) {
  qRegisterMetaType<QVector<Animal*> >("QVector<Animal*>");

  simulation_animal = new MainAnimal;

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
  //simulation_animal->setSimulation(this);
  connect(simulation_animal, SIGNAL(resultReady(int, int, char)), this, SLOT(handleResults(int, int, char)));
  connect(simulation_animal, SIGNAL(effacer()), this, SLOT(slot_effacer()));

}

Simulation::~Simulation() {}

void Simulation::slot_setTailleX(int x) {
  tailleX = x;
  terrain->setRect(0, 0, tailleX, tailleY);
  simulation_animal->setTailleX(tailleX/32);
}

void Simulation::slot_setTailleY(int y) {
  tailleY = y;
  terrain->setRect(0, 0, tailleX, tailleY);
  simulation_animal->setTailleY(tailleY/32);
}

void Simulation::slot_simulation_animal() {
  //simulation_animal->doWork();
  if (simu_en_cours == false) {
    //this->start_simulation();
    simulation_animal->start();
    simu_en_cours = true;
  } else {
    //this->terminate_simulation();
    simulation_animal->terminate();
    simu_en_cours = false;
  }
}

void Simulation::start_simulation() {
  QGraphicsPixmapItem *temp = new QGraphicsPixmapItem();
  //
  // tab2Dimage = new QGraphicsPixmapItem*[tailleY / 32];
  // for ( int i = 0; i < tailleY / 32; i++)
  // tab2Dimage[i] = new QGraphicsPixmapItem[tailleX / 32];
  //
  // for (int i = 0; i < tailleY / 32; i++) {
  //   for (int j = 0; j < tailleX / 32; j++) {
  //     //tab2Dimage[i][j] = new QGraphicsPixmapItem();
  //   }
  // }
  for (int i = 0; i < nb_animaux; i++) {
    tab_image << temp;
  }
}

void Simulation::terminate_simulation() {
  // for (int i = 0; i < tailleY / 32; i++) {
  //   for (int j = 0; j < tailleX / 32; j++) {
  //     if (tab2Dimage[i][j].hasFocus() == true) {
  //     //  this->removeItem(tab2Dimage[i][j]);
  //     }
  //   }
  // }

  // for ( int i = 0; i < tailleX / 32; i++)
  // delete tab2Dimage[i];
  // delete tab2Dimage;

  for (int i = 0; i < nb_animaux; i++) {
    this->removeItem(tab_image.value(i));
    tab_image.removeAt(i);
  }
}

void Simulation::slot_nb_animaux(int nb_anim) {
  nb_animaux = nb_anim;
  simulation_animal->setNbAnimaux(nb_animaux);
}

void Simulation::slot_effacer() {
  for (int i = 0; i < tab_image.size(); i++) {
     this->removeItem(tab_image.value(i));
     tab_image.removeAt(i);
  }
}

void Simulation::handleResults(int x, int y, char id) {
  //int x, y;
  //char id;
  // for (int i = 0; i < tab_image.size(); i++) {
  //    this->removeItem(tab_image.value(i));
  //    tab_image.removeAt(i);
  // }


  QGraphicsPixmapItem *temp = new QGraphicsPixmapItem();
  //for (int i = 0; i < nb_animaux; i++) {
    // id = vect[i]->getID();
    // x = vect[i]->getX() * 32;
    // y = vect[i]->getY() * 32;
    //this->removeItem(tab_image.value(i));
    qDebug() << "id de l'animal" << id << "pos : " << x << y;
    if (id == 'L') {
      qDebug() << "lion";
       temp->setPixmap(lion);
       temp->setPos(x*32, y*32);
       tab_image << temp;
       this->addItem(tab_image.last());
     } else if (id == 'G') {
       qDebug() << "gazelle";
       temp->setPixmap(gazelle);
       temp->setPos(x*32, y*32);
       tab_image << temp;
       this->addItem(tab_image.last());
      //  tab_image.value(i)->setPixmap(gazelle);
      //  tab_image.value(i)->setPos(x, y);
      //  this->addItem(tab_image.value(i));
     } else if (id == 'X') {
       qDebug() << "mort";
       temp->setPixmap(tombe);
       temp->setPos(x*32, y*32);
       tab_image << temp;
       this->addItem(tab_image.last());
      //  tab_image.value(i)->setPixmap(tombe);
      //  tab_image.value(i)->setPos(x, y);
      //  this->addItem(tab_image.value(i));
     } else if (id == 'M') {
       qDebug() << "mange";
       temp->setPixmap(gigot);
       temp->setPos(x*32, y*32);
       tab_image << temp;
       this->addItem(tab_image.last());
      //  tab_image.value(i)->setPixmap(gigot);
      //  tab_image.value(i)->setPos(x, y);
      //  this->addItem(tab_image.value(i));
     } else {
       qDebug() << "aucun ??!?!";
     }
  }
    // if (vect->getID() == 'L') {
    //    tab_image.value()
    //    //tab2Dimage[i][j].setPixmap(lion);
    //    //tab2Dimage[i][j].setPos(i * 32, j * 32);
    //    //this->addItem(tab2Dimage[i][j]);
    //  }// else if (element == 'G') {
      //  temp->setPixmap(gazelle);
      //  temp->setPos(x, y);
      //  tab_image.append(temp);
      //  this->addItem(tab_image.value(i));
     //} else if (element == 'X') {
      //  temp->setPixmap(tombe);
      //  temp->setPos(x, y);
      //  tab_image.append(temp);
      //  this->addItem(tab_image.value(i));
     //} else if (element == 'M') {
      //  temp->setPixmap(gigot);
      //  temp->setPos(x, y);
      //  tab_image.append(temp);
      //  this->addItem(tab_image.value(i));
     //}

//}
