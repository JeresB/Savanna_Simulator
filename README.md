# Savanna Simulator
Permet de lancer une simulation entre chasseurs(lions) et proies(gazelles)

INSTALL :
  3 lignes de commande à effectuer
  Utilisation de QT version 5.8 !!!

  qmake -project
    ajout de la ligne suivante dans le fichier .pro
      QT += widgets charts gui multimedia
  qmake
    ajout de -std=c++11 dans la ligne CXXFLAGS dans le makefile
  make
