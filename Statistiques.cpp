#include "Statistiques.hpp"

Statistiques::Statistiques(QWidget *parent) : QWidget(parent) {
  this->setMinimumSize(800, 400);

  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);

  qbl_general = new QHBoxLayout;
  // Création du widget principale
  this->setLayout(qbl_general);

  chart = new QChart();
  pie = new QPieSeries();
  pie->setVerticalPosition(0.6);

  pie->append("Lions vivants", 20);
  pie->append("Gazelles vivantes", 20);
  pie->append("Animaux morts", 0);
  pie->append("Gazelles mangees", 0);
  pie->append("Vegetaux", 10);

  chart->addSeries(pie);
  chart->setTitle("Statistiques de la Simulation");

  lion = pie->slices().at(0);
  gazelle = pie->slices().at(1);
  mort = pie->slices().at(2);
  manger = pie->slices().at(3);
  vegetal = pie->slices().at(4);

  graphique = new QChartView(chart);
  graphique->setRenderHint(QPainter::Antialiasing);

  qbl_general->addWidget(graphique);
  qbl_general->addWidget(BuildTexteAffichage());

  connect(pie, SIGNAL(hovered(QPieSlice*, bool)), this, SLOT(slot_hover_slice(QPieSlice*, bool)));
}

Statistiques::~Statistiques(){}

void Statistiques::update() {
  lion_label->setText("Lions vivants : " + QString::number(lion_vivant));
  gazelle_label->setText("Gazelles vivantes : " + QString::number(gazelle_vivante));
  mort_label->setText("Animaux Morts : " + QString::number(animaux_mort));
  manger_label->setText("Gazelles mangées : " + QString::number(gazelle_mangees));
  vegetal_label->setText("Vegetaux : " + QString::number(vegetal_vivant));
}

QGroupBox* Statistiques::BuildTexteAffichage() {
  QGroupBox *box_texte = new QGroupBox("Statistiques Valeurs");

  QVBoxLayout *valeurs = new QVBoxLayout;

  lion_label = new QLabel("Lions vivants : 20");
  gazelle_label = new QLabel("Gazelles vivantes : 20");
  mort_label = new QLabel("Animaux Morts : 0");
  manger_label = new QLabel("Gazelles mangées : 0");
  vegetal_label = new QLabel("Vegataux : 10");

  valeurs->addWidget(lion_label);
  valeurs->addWidget(gazelle_label);
  valeurs->addWidget(mort_label);
  valeurs->addWidget(manger_label);
  valeurs->addWidget(vegetal_label);

  box_texte->setLayout(valeurs);

  return box_texte;
}

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

void Statistiques::slot_hover_slice(QPieSlice* slice, bool state) {
  slice->setExploded(state);
  slice->setLabelVisible(state);
}
