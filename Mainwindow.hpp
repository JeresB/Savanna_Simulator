#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QGraphicsView>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>

#include "Simulation.hpp"
#include "Statistiques.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow(){};

    QGroupBox *BuildGroupBoxControle();

  public slots:
    void slot_pleinecran();
    void slot_statistiques();

  private:
    QWidget *widget_general;
    QGraphicsView *myview;

    QGroupBox *group_box;
    QBoxLayout *box_layout;
    QVBoxLayout *simu_controle1;
    QVBoxLayout *simu_controle2;
    QVBoxLayout *simu_controle3;
    QVBoxLayout *box_control;

    QLabel *nb_animaux_label;
    QSlider *nb_animaux_simu;
    QLabel *proportion_label;
    QSlider *proportion_simu;
    QLabel *vitesse_label;
    QSlider *vitesse_simu;

    QLabel *energie_label;
    QSlider *energie_simu;
    QLabel *tailleX_label;
    QSlider *tailleX_simu;
    QLabel *tailleY_label;
    QSlider *tailleY_simu;

    QPushButton *simulation_bouton;
    QPushButton *statistiques;

    QCheckBox *plein_ecran;
    QPushButton *quitter;

    Statistiques *statistiquesWindow;
    Simulation *simulation;
};

#endif
