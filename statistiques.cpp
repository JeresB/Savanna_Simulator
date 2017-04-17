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

  lion = new QSplineSeries();
  gazelle = new QSplineSeries();
  chart->addSeries(lion);
  chart->addSeries(gazelle);
  chart->setTitle("Simple areachart example");
  chart->createDefaultAxes();
  chart->axisX()->setRange(0, 100);
  chart->axisY()->setRange(0, 50);

  graphique = new QChartView(chart);
  graphique->setRenderHint(QPainter::Antialiasing);

  qbl_general->addWidget(graphique);
}

Statistiques::~Statistiques(){}

void Statistiques::update() {}

void Statistiques::slot_resultat_valeur(int l, int g, int t) {
  int m = t / 1000;
  lion->append(m, l);
  gazelle->append(m, g);
}
