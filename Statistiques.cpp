// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Statistiques.cpp                                                  ----- //
// ----- Type         : source                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée un affichage graphique                             ----- //
// -------------------------------------------------------------------------------------------- //
#include "Statistiques.hpp"

// Constructeur
Statistiques::Statistiques(QWidget *parent) : QWidget(parent) {
  // Taille minimum de la fenêtre de statistiques
  this->setMinimumSize(800, 400);

  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);

  // Création du layout principal
  qbl_general = new QHBoxLayout;
  this->setLayout(qbl_general);

  // Création du graphique
  chart = new QChart();
  // Création du camembert
  pie = new QPieSeries();
  // Position du camembert
  pie->setVerticalPosition(0.6);

  // ----- Initialisation de chaque tranches du camembert --------------------------------------- //
  pie->append("Lions vivants", 20);
  pie->append("Gazelles vivantes", 20);
  pie->append("Animaux morts", 0);
  pie->append("Gazelles mangees", 0);
  pie->append("Vegetaux", 10);
  // -------------------------------------------------------------------------------------------- //

  // Ajout du camembert au graphique
  chart->addSeries(pie);
  // Nom du graphique
  chart->setTitle("Statistiques de la Simulation");

  // ----- Récuperation de chaque tranches de camembert ----------------------------------------- //
  lion = pie->slices().at(0);
  gazelle = pie->slices().at(1);
  mort = pie->slices().at(2);
  manger = pie->slices().at(3);
  vegetal = pie->slices().at(4);
  // -------------------------------------------------------------------------------------------- //

  // Ajout du graphique à la vue graphique
  graphique = new QChartView(chart);
  graphique->setRenderHint(QPainter::Antialiasing);

  // Ajout du graphique et de l'affichage texte au layout
  qbl_general->addWidget(graphique);
  qbl_general->addWidget(BuildTexteAffichage());

  // Connect pour contrôler l'hover sur les tranches du camembert
  connect(pie, SIGNAL(hovered(QPieSlice*, bool)), this, SLOT(slot_hover_slice(QPieSlice*, bool)));
}

// Destructeur
Statistiques::~Statistiques(){}

// Mise à jour des données
void Statistiques::update() {
  lion_label->setText("Lions vivants : " + QString::number(lion_vivant));
  gazelle_label->setText("Gazelles vivantes : " + QString::number(gazelle_vivante));
  mort_label->setText("Animaux Morts : " + QString::number(animaux_mort));
  manger_label->setText("Gazelles mangées : " + QString::number(gazelle_mangees));
  vegetal_label->setText("Vegetaux : " + QString::number(vegetal_vivant));
}

// Création d'un affichage en texte
QGroupBox* Statistiques::BuildTexteAffichage() {
  // Groupe Box
  QGroupBox *box_texte = new QGroupBox("Statistiques Valeurs");

  // Layout vertical
  QVBoxLayout *valeurs = new QVBoxLayout;

  // ----- Label des données -------------------------------------------------------------------- //
  lion_label = new QLabel("Lions vivants : 20");
  gazelle_label = new QLabel("Gazelles vivantes : 20");
  mort_label = new QLabel("Animaux Morts : 0");
  manger_label = new QLabel("Gazelles mangées : 0");
  vegetal_label = new QLabel("Vegataux : 10");
  // -------------------------------------------------------------------------------------------- //

  // ----- Ajout des labels --------------------------------------------------------------------- //
  valeurs->addWidget(lion_label);
  valeurs->addWidget(gazelle_label);
  valeurs->addWidget(mort_label);
  valeurs->addWidget(manger_label);
  valeurs->addWidget(vegetal_label);
  // -------------------------------------------------------------------------------------------- //

  // définition du layout vertical au groupe box
  box_texte->setLayout(valeurs);

  // On retourne le groupe box
  return box_texte;
}

// Slot : met à jour les valeurs et des tranches de camembert
void Statistiques::slot_resultat_valeur(int l, int g, int mo, int ma, int ve) {
  lion->setValue(l);
  gazelle->setValue(g);
  mort->setValue(mo);
  manger->setValue(ma);
  vegetal->setValue(ve);

  lion_vivant = l;
  gazelle_vivante = g;
  animaux_mort = mo;
  gazelle_mangees = ma;
  vegetal_vivant = ve;
}

// Slot : si on passe la souris sur une tranche de camembert
void Statistiques::slot_hover_slice(QPieSlice* slice, bool state) {
  slice->setExploded(state); // Affichage de la tranche en plus grand
  slice->setLabelVisible(state); // Affichage de la legende
}
