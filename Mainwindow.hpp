// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : MainWindow.hpp                                                    ----- //
// ----- Type         : header                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée une fenêtre graphique                              ----- //
// -------------------------------------------------------------------------------------------- //
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QLayout>
#include <QGraphicsView>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>

#include "Simulation.hpp"
#include "Statistiques.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    // Constructeur et Destructeur
    MainWindow(QWidget *parent = 0);
    ~MainWindow(){};

    // Méthodes
    QGroupBox *BuildGroupBoxControle();
    void setValueSlider(int value, int i);

  public slots:
    void slot_pleinecran();
    void slot_statistiques();
    void slot_configuration();

  private:
    QWidget *widget_general; // widget principal
    QGraphicsView *myview; // vue de la simulation

    // ----- Layouts ---------------------------------------------------------------------------- //
    QGroupBox *group_box;
    QBoxLayout *box_layout;
    QVBoxLayout *simu_controle1;
    QVBoxLayout *simu_controle2;
    QVBoxLayout *simu_controle3;
    QVBoxLayout *box_control;
    // ------------------------------------------------------------------------------------------ //

    // ----- Création des contôles et de leurs labels respectifs -------------------------------- //
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
    QPushButton *config;

    QCheckBox *plein_ecran;
    QPushButton *quitter;

    QLabel *signature;
    // ------------------------------------------------------------------------------------------ //

    Statistiques *statistiquesWindow; // Fenêtre de stats
    Simulation *simulation; // Simulation
};

#endif
