// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : MainWindow.cpp                                                    ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une fenêtre graphique                              ----- //
// -------------------------------------------------------------------------------------------- //
#include "Mainwindow.hpp"

// Constructeur
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Savanna Simulator"); // Nom de la fenêtre

  // Création du widget et du layout
  widget_general = new QWidget;
  QVBoxLayout *qbl_general = new QVBoxLayout;

  // Initialisation du widget et du layout
  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);

  // Fenêtre de statistiques
  statistiquesWindow = new Statistiques;

  // Création de la scène de simulation
  simulation = new Simulation(statistiquesWindow, this);
  simulation->setBackgroundBrush(QColor(47, 139, 14));
  myview = new QGraphicsView(simulation, this);

  // Ajout des contrôles et de la simulation au layout
  qbl_general->addWidget(BuildGroupBoxControle());
  qbl_general->addWidget(myview);
}

// Création du groupe box de contrôle
QGroupBox *MainWindow::BuildGroupBoxControle() {
  // Groupe Box contenant tous les contôles
  // VOIR SCHEMA DETAILLE
  group_box = new QGroupBox(tr("Contrôle"));

  // Layout Box orienté de gauche à droite
  // Contient tous les layouts
  box_layout = new QBoxLayout(QBoxLayout::LeftToRight);

  // Layout contenant : simulation, stats, plein écran et quitter
  QBoxLayout *box_layout_controle = new QBoxLayout(QBoxLayout::LeftToRight);
  // Layout contenant : box_layout_controle + le label de signature
  QBoxLayout *box_layout_controle_signature = new QBoxLayout(QBoxLayout::TopToBottom);

  // ------ Layout Box --------------------------------------------------------------- //

  // Contient les sliders : nombre d'animaux, proportion lion/gazelle, vitesse.
  simu_controle1 = new QVBoxLayout;
  // Contient les sliders : energie, taille en X et Y.
  simu_controle2 = new QVBoxLayout;
  // Contient les boutons : démarrage / arrêt de la simulation et la fenêtre des statistiques.
  simu_controle3 = new QVBoxLayout;
  // Contient la check box plein écran et le bouton d'arrêt du programme.
  box_control = new QVBoxLayout;
  // Contient la signature
  QHBoxLayout* box_signature = new QHBoxLayout;
  // -------------------------------------------------------------------------------------------- //

  // ------ Création des sliders : -------------------------------------------------------------- //
              // 1) Label du slider
              // 2) Création du slider horizontal
              // 3) Initialisation des valeurs minimum et maximum du slider
              // 4) Initialisation d'une valeur pour le slider

  // Slider : nombre d'animaux
  nb_animaux_label = new QLabel("Nombres d'animaux initials", this);
  nb_animaux_simu = new QSlider(Qt::Horizontal);
  nb_animaux_simu->setRange(10, 200);

  // Slider : proportion lion / gazelle
  proportion_label = new QLabel("Proportion Lions / Gazelles", this);
  proportion_simu = new QSlider(Qt::Horizontal);
  proportion_simu->setRange(2, 20);

  // Slider : vitesse de la simulation
  vitesse_label = new QLabel("Vitesse de la simulation", this);
  vitesse_simu = new QSlider(Qt::Horizontal);
  vitesse_simu->setRange(1, 1000);

  // Slider : energie initiale
  energie_label = new QLabel("Energie initiale", this);
  energie_simu = new QSlider(Qt::Horizontal);
  energie_simu->setRange(100, 1000);

  // Slider : taille en X du terrain de la simulation
  tailleX_label = new QLabel("Taille Horizontale", this);
  tailleX_simu = new QSlider(Qt::Horizontal);
  tailleX_simu->setRange(100, 1300);

  // Slider : taille en Y du terrain de la simulation
  tailleY_label = new QLabel("Taille Verticale", this);
  tailleY_simu = new QSlider(Qt::Horizontal);
  tailleY_simu->setRange(100, 550);
  // -------------------------------------------------------------------------------------------- //

  // Bouton Simulation : 2 Fonctions
          // 1) Démarre la simulation
          // 2) Arrête la simulation
  simulation_bouton = new QPushButton("Simulation", this);

  // Bouton pour afficher ou quitter la fenêtre des statistiques
  statistiques = new QPushButton("Statistiques", this);

  // Bouton pour choisir un fichier de config
  config = new QPushButton("Configuration", this);

  // Check Box pour activer / désactiver le plein écran
  plein_ecran = new QCheckBox("Plein Ecran", this);

  // Bouton pour quitter le programme
  quitter = new QPushButton("Quitter", this);

  // Label de signature
  signature = new QLabel("</> Jeremy </>", this);

  // ------ Ajout de tous les widgets (label, slider, bouton) à leurs layouts respectifs -------- //
  simu_controle1->addWidget(nb_animaux_label);
  simu_controle1->addWidget(nb_animaux_simu);
  simu_controle1->addWidget(proportion_label);
  simu_controle1->addWidget(proportion_simu);
  simu_controle1->addWidget(vitesse_label);
  simu_controle1->addWidget(vitesse_simu);
  simu_controle2->addWidget(energie_label);
  simu_controle2->addWidget(energie_simu);
  simu_controle2->addWidget(tailleX_label);
  simu_controle2->addWidget(tailleX_simu);
  simu_controle2->addWidget(tailleY_label);
  simu_controle2->addWidget(tailleY_simu);
  simu_controle3->addWidget(simulation_bouton);
  simu_controle3->addWidget(statistiques);
  simu_controle3->addWidget(config);
  box_control->addWidget(plein_ecran);
  box_control->addWidget(quitter);
  box_signature->addWidget(signature);
  box_signature->setAlignment(signature, Qt::AlignHCenter);
  // -------------------------------------------------------------------------------------------- //

  // Ajout de layouts
  box_layout_controle->addLayout(simu_controle3);
  box_layout_controle->addLayout(box_control);

  box_layout_controle_signature->addLayout(box_layout_controle);
  box_layout_controle_signature->addLayout(box_signature);

  // ------ Ajout des 4 layouts au Layout principal
  box_layout->addLayout(simu_controle1);
  box_layout->addLayout(simu_controle2);
  box_layout->addLayout(box_layout_controle_signature);
  // -------------------------------------------------------------------------------------------- //

  // Enfin : Ajout du layout principal à la groupe box
  group_box->setLayout(box_layout);

  // -------------------------------------------------------------------------------------------- //
  // ------ Connexion de tous les contrôles ----------------------------------------------------- //
  // -------------------------------------------------------------------------------------------- //
      // 1) nombres d'animaux
  connect(nb_animaux_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_nb_animaux(int)));
      // 2) proportion lion / gazelle
  connect(proportion_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setProportion(int)));
      // 3) vitesse de la simulation
  connect(vitesse_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_vitesse(int)));
      // 4) energie initiale
  connect(energie_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setEnergie(int)));
      // 5) taille en X
  connect(tailleX_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setTailleX(int)));
      // 6) taille en Y
  connect(tailleY_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setTailleY(int)));
      // 7) démarre / arrête la simulation
  connect(simulation_bouton, SIGNAL(clicked()), simulation, SLOT(slot_simulation()));
      // 8) affiche / quitte la fenêtre de statistiques
  connect(statistiques, SIGNAL(clicked()), this, SLOT(slot_statistiques()));
      // 9) Permet de choisir un fichier de Configuration
  connect(config, SIGNAL(clicked()), this, SLOT(slot_configuration()));
      // 10) type d'affichage de la fenêtre principale
  connect(plein_ecran, SIGNAL(clicked()), this, SLOT(slot_pleinecran()));
      // 11) quitte le programme
  connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
  // -------------------------------------------------------------------------------------------- //
  // -------------------------------------------------------------------------------------------- //
  // -------------------------------------------------------------------------------------------- //

  // On donne un valeur à chaque slider
  // Astuce : les slots liés aux sliders vont se déclencher
  // Tous les données vont donc s'afficher dans la console
  nb_animaux_simu->setValue(50);
  proportion_simu->setValue(2);
  vitesse_simu->setValue(980);
  energie_simu->setValue(200);
  tailleX_simu->setValue(500);
  tailleY_simu->setValue(300);
  // -------------------------------------------------------------------------------------------- //

  // On retourne la groupe box pour l'afficher dans le widget principal du programme
  return group_box;
}

// ---------------------------------------------------------------------------------------------- //
// ------ SLOT : Change le mode de la fenêtre principale ---------------------------------------- //
// ------ Plein écran / fenêtré ----------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
void MainWindow::slot_pleinecran() {
  if(plein_ecran->isChecked()) qDebug() << "[INFO] : Plein écran activé !";
  else qDebug() << "[INFO] : Plein écran désactivé !";

  // Change l'état de la fenêtre
  this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
}

// ---------------------------------------------------------------------------------------------- //
// ------ SLOT : Ouvre ou ferme la fenêtre de statistiques -------------------------------------- //
// ---------------------------------------------------------------------------------------------- //
void MainWindow::slot_statistiques() {
  if (statistiquesWindow->isVisible()) {
    statistiquesWindow->hide();
    qDebug() << "[INFO] : Fermeture de la fenêtre de statistiques !";
  } else {
    statistiquesWindow->show();
    qDebug() << "[INFO] : Ouverture de la fenêtre de statistiques !";
  }
}

// ---------------------------------------------------------------------------------------------- //
// ------ SLOT : Ouvre une petite fenêtre qui demande le fichier de config ---------------------- //
// ---------------------------------------------------------------------------------------------- //
void MainWindow::slot_configuration() {
  // Variables utilisées
  QString file, texte;
  int compteur = 0;

  // Ouverture d'une petite fenêtre qui demande le nom du fichier
  file = QInputDialog::getText(NULL,"Fichier","Choississez un fichier de configuration !");

  // On crée un QFile avec le nom du fichier et on lui ajout ".conf"
  QFile fichier(file + ".conf");
  // Si on réussi à ouvrir le fichier en lecture seulement
  if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // Création d'un flux permet de parcourir le fichier
    QTextStream flux(&fichier);
    // Pour chaque ligne (21 nombres de ligne dans les fichiers de configuration)
    for (int i = 0; i < 21; i++) {
      // On lit la ligne
      texte = flux.readLine();

      // Si la ligne commence par un #
      // On ne fait rien c'est un commentaire
      if (!texte.startsWith("#")) {
        // Récuperation de la valeur
        // On la convertie en entier
        bool ok;
        int value = texte.toInt(&ok, 10);
        // On appel la fonction qui met à jour les sliders
        setValueSlider(value, compteur);
        // Ce compteur permet de savoir quel valeur on modifie
        compteur++;
      }
    }
  }

  // On ferme le fichier
  fichier.close();
}

// Fonction qui met à jour les sliders en fonction d'un fichier .conf
void MainWindow::setValueSlider(int value, int i) {
  // Argument la valeur à modifer et l'ordre du slider
  switch (i) {
    case 0:
      nb_animaux_simu->setValue(value);
    break;
    case 1:
      proportion_simu->setValue(value);
    break;
    case 2:
      vitesse_simu->setValue(value);
    break;
    case 3:
      energie_simu->setValue(value);
    break;
    case 4:
      tailleX_simu->setValue(value);
    break;
    case 5:
      tailleY_simu->setValue(value);
    break;
  }
}
