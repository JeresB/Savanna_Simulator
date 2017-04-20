#include "statistiques.hpp"

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

  pie->append("Lions vivants", 25);
  pie->append("Gazelles vivantes", 25);
  pie->append("Animaux morts", 0);
  pie->append("Gazelles mangees", 0);

  chart->addSeries(pie);
  chart->setTitle("Statistiques de la Simulation");

  lion = pie->slices().at(0);
  gazelle = pie->slices().at(1);
  mort = pie->slices().at(2);
  manger = pie->slices().at(3);
  // slice->setExploded();
  // slice->setLabelVisible();
  // slice->setPen(QPen(Qt::darkGreen, 2));
  // slice->setBrush(Qt::green);


  graphique = new QChartView(chart);
  graphique->setRenderHint(QPainter::Antialiasing);

  qbl_general->addWidget(graphique);
  qbl_general->addWidget(BuildTexteAffichage());
}

Statistiques::~Statistiques(){}

void Statistiques::update() {
  lion_label->setText("Lions vivants : " + QString::number(lion_vivant));
  gazelle_label->setText("Gazelles vivantes : " + QString::number(gazelle_vivante));
  mort_label->setText("Animaux Morts : " + QString::number(animaux_mort));
  manger_label->setText("Gazelles mangées : " + QString::number(gazelle_mangees));
}

QGroupBox* Statistiques::BuildTexteAffichage() {
  QGroupBox *box_texte = new QGroupBox("Statistiques Valeurs");

  QVBoxLayout *valeurs = new QVBoxLayout;
  int l = 25;

  lion_label = new QLabel("Lions vivants : 25");
  gazelle_label = new QLabel("Gazelles vivantes : 25");
  mort_label = new QLabel("Animaux Morts : 0");
  manger_label = new QLabel("Gazelles mangées : 0");

  valeurs->addWidget(lion_label);
  valeurs->addWidget(gazelle_label);
  valeurs->addWidget(mort_label);
  valeurs->addWidget(manger_label);

  box_texte->setLayout(valeurs);

  return box_texte;
}

void Statistiques::slot_resultat_valeur(int l, int g, int mo, int ma) {
  lion->setValue(l);
  gazelle->setValue(g);
  mort->setValue(mo);
  manger->setValue(ma);
  if(l < 0) lion_vivant = 0;
  else lion_vivant = l;
  if(g < 0) gazelle_vivante = 0;
  else gazelle_vivante = g;
  animaux_mort = mo;
  gazelle_mangees = ma;
}
