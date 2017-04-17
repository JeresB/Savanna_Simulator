#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QMenu>
#include <QGroupBox>
#include <QPushButton>
#include <QMenuBar>
#include <QGraphicsView>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include "console.hpp"
#include "simulation.hpp"
#include "statistiques.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGroupBox *BuildGroupBoxControle();

  public slots:
    void slot_simulation();
    void slot_pleinecran();
    void slot_console();
    void slot_statistiques();

  private:
    QWidget *widget_general;

    QMenu *menuFichier;

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
    QPushButton *console;
    QPushButton *quitter;

    Console *consoleWindow;
    bool console_ok = false;
    bool statistiques_ok = false;
    Statistiques *statistiquesWindow;

    QGraphicsView *myview;

    Simulation *simulation;
};

#endif
