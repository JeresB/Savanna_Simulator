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
#include <QSplineSeries>
using namespace QtCharts;

class Statistiques : public QWidget {
  Q_OBJECT

  public:
    explicit Statistiques(QWidget *parent = 0);
    ~Statistiques();

  signals:

  public slots:
    void update();
    void slot_resultat_valeur(int, int, int);

  private:
    QTimer *timer;
    QHBoxLayout *qbl_general;

    QChartView *graphique;
    QChart *chart;
    QSplineSeries* lion;
    QSplineSeries* gazelle;

};

#endif
