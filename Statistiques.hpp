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
    void slot_resultat_valeur(int, int, int, int, int);
    void slot_hover_slice(QPieSlice* slice, bool state);

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
    QPieSlice* vegetal;

    QLabel* lion_label;
    QLabel* gazelle_label;
    QLabel* mort_label;
    QLabel* manger_label;
    QLabel* vegetal_label;

    int lion_vivant = 20;
    int gazelle_vivante = 20;
    int animaux_mort = 0;
    int gazelle_mangees = 0;
    int vegetal_vivant = 10;

};

#endif
