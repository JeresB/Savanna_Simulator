#include "mainAnimal.hpp"

MainAnimal::MainAnimal() {}

MainAnimal::~MainAnimal() {}

void MainAnimal::setNbAnimaux(int nb_anim) {
  nb_animaux = nb_anim;
}

void MainAnimal::setTailleX(int x) {
  max_x = x;
}

void MainAnimal::setTailleY(int y) {
  max_y = y;
}

void MainAnimal::run() {
  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(100);
  doWork();
}

void MainAnimal::doWork() {
    //int x, y;
    char element;
    //int nb;
    monde = new Monde(nb_animaux, max_x, max_y);

     while(monde->getNbMort() < monde->getNbAnimaux()) {
       monde->passeuntour();
    //   //y = monde.getMAX_Y();
    //   //x = monde.getMAX_X();
    //   //nb = monde.getNbAnimaux();
       //QVector<Animal*> qvect_anim = QVector<Animal*>::fromStdVector(monde->getVect());
    //   // for (int i = 0; i < monde.getMAX_Y(); i++) {
    //   //   for (int j = 0; j < monde.getMAX_X(); j++) {
    //   //     element = monde.getElementTab2D(i, j);
    //   //     emit resultReady(element, i, j);
    //   //   }
    //   // }
    //   //QVector<T> qVec = QVector<T>::fromStdVector(stdVec);
      std::vector<Animal*> vect = monde->getVect();
      int x, y;
      char id;
      for (int i = 0; i < vect.size(); i++) {
        x = vect[i]->getX();
        y = vect[i]->getY();
        id = vect[i]->getID();
        emit resultReady(x, y, id);
        usleep(2000);
      }
      sleep(1);
      emit effacer();


    //
    //
     }
}

void MainAnimal::update() {
  //if(monde->getNbMort() < monde->getNbAnimaux()) {
    //monde->passeuntour();
  //
  //   QVector<Animal*> qvect_anim = QVector<Animal*>::fromStdVector(monde->getVect());
  //   emit resultReady(qvect_anim);
  //}
}
