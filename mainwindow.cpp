#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Predator"); // Nom de la fenêtre

  widget_general = new QWidget;
  QVBoxLayout *qbl_general = new QVBoxLayout;

  // Création du widget principale
  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);

  // Création de la scène de jeu
  simulation = new Simulation(this);
  simulation->setBackgroundBrush(QColor(13, 139, 242));
  myview = new QGraphicsView(simulation, this);

  qbl_general->addWidget(BuildGroupBoxControle());
  qbl_general->addWidget(myview);

  // Création du menu et ajout de nos actions
  menuFichier = menuBar()->addMenu(tr("&Fichier"));

  consoleWindow = new Console;
}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  group_box = new QGroupBox(tr("Contrôle"));

  box_layout = new QBoxLayout(QBoxLayout::LeftToRight);

  simu_controle1 = new QVBoxLayout;
  simu_controle2 = new QVBoxLayout;
  simu_controle3 = new QVBoxLayout;
  box_control = new QVBoxLayout;

  nb_animaux_label = new QLabel("Nombres d'animaux initials", this);
  nb_animaux_simu = new QSlider(Qt::Horizontal);
  nb_animaux_simu->setRange(10, 200);
  proportion_label = new QLabel("Proportion Lions / Gazelles", this);
  proportion_simu = new QSlider(Qt::Horizontal);
  proportion_simu->setRange(1, 10);
  vitesse_label = new QLabel("Vitesse de la simulation", this);
  vitesse_simu = new QSlider(Qt::Horizontal);
  vitesse_simu->setRange(1, 50);

  energie_label = new QLabel("Energie initiale", this);
  energie_simu = new QSlider(Qt::Horizontal);
  energie_simu->setRange(100, 1000);
  tailleX_label = new QLabel("Taille Horizontale", this);
  tailleX_simu = new QSlider(Qt::Horizontal);
  tailleX_simu->setRange(100, 1300);
  tailleY_label = new QLabel("Taille Verticale", this);
  tailleY_simu = new QSlider(Qt::Horizontal);
  tailleY_simu->setRange(100, 550);

  simulation_bouton = new QPushButton("Simulation", this);

  plein_ecran = new QPushButton("Plein Ecran", this);
  console = new QPushButton("Console", this);
  quitter = new QPushButton("Quitter", this);

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

  box_control->addWidget(plein_ecran);
  box_control->addWidget(console);
  box_control->addWidget(quitter);

  box_layout->addLayout(simu_controle1);
  box_layout->addLayout(simu_controle2);
  box_layout->addLayout(simu_controle3);
  box_layout->addLayout(box_control);

  group_box->setLayout(box_layout);

  connect(nb_animaux_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_nb_animaux(int)));
  connect(vitesse_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_vitesse(int)));
  connect(energie_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setEnergie(int)));
  connect(tailleX_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setTailleX(int)));
  connect(tailleY_simu, SIGNAL(valueChanged(int)), simulation, SLOT(slot_setTailleY(int)));

  connect(simulation_bouton, SIGNAL(clicked()), simulation, SLOT(slot_simulation_animal()));

  connect(plein_ecran, SIGNAL(clicked()), this, SLOT(slot_pleinecran()));
  connect(console, SIGNAL(clicked()), this, SLOT(slot_console()));
  connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

  group_box->setAlignment(Qt::AlignTop);
  return group_box;
}

void MainWindow::slot_pleinecran() {
  consoleWindow->log("[CONNEXION] : Changement du mode de l'écran en cours ...");
  this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
}

void MainWindow::slot_console() {
  if (console_ok == false) {
    consoleWindow->show();
    console_ok = true;
  } else {
    consoleWindow->hide();
    console_ok = false;
  }
}
