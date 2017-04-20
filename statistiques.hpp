#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QHBoxLayout>
#include <QtCharts>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QBoxLayout>
#include <QGroupBox>
using namespace QtCharts;

class Statistiques : public QWidget {
  Q_OBJECT

  public:
    explicit Statistiques(QWidget *parent = 0);
    ~Statistiques();
    QGroupBox* BuildTexteAffichage();

  signals:

  public slots:
    void update();
    void slot_resultat_valeur(int, int, int, int);

  private:
    QTimer *timer;
    QHBoxLayout *qbl_general;

    QChartView *graphique;
    QChart *chart;
    QPieSeries* pie;
    QPieSlice* lion;
    QPieSlice* gazelle;
    QPieSlice* mort;
    QPieSlice* manger;

    QLabel* lion_label;
    QLabel* gazelle_label;
    QLabel* mort_label;
    QLabel* manger_label;

    int lion_vivant = 25;
    int gazelle_vivante = 25;
    int animaux_mort = 0;
    int gazelle_mangees = 0;

};

#endif
