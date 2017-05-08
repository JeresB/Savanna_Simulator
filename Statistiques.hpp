// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Statistiques.hpp                                                  ----- //
// ----- Type         : header                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée un affichage graphique                             ----- //
// -------------------------------------------------------------------------------------------- //
#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QWidget>
#include <QLayout>
#include <QtCharts>

class Statistiques : public QWidget {
  Q_OBJECT

  public:
    // Constructeur et destructeur
    explicit Statistiques(QWidget *parent = 0);
    ~Statistiques();

    // Methode : Affiche les données
    QGroupBox* BuildTexteAffichage();

  public slots:
    // Mise à jour des données
    void update();
    // Récupère les données
    void slot_resultat_valeur(int, int, int, int, int);
    // Si on passe la souris sur une tranche de camembert
    void slot_hover_slice(QPieSlice* slice, bool state);

  private:
    QTimer *timer; // Timer
    QHBoxLayout *qbl_general; // Layout principal

    QChartView *graphique; // Layout du graphique camembert
    QChart *chart; // Graphique
    QPieSeries* pie; // Camembert

    // ------------------------------------------------------------------------------------------- //
    // ------ Tranche de camembert pour chaques données ------------------------------------------ //
    // ------------------------------------------------------------------------------------------- //
    QPieSlice* lion;
    QPieSlice* gazelle;
    QPieSlice* mort;
    QPieSlice* manger;
    QPieSlice* vegetal;
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //

    // ------------------------------------------------------------------------------------------- //
    // ------ Label pour chaques données --------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //
    QLabel* lion_label;
    QLabel* gazelle_label;
    QLabel* mort_label;
    QLabel* manger_label;
    QLabel* vegetal_label;
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //

    // ------------------------------------------------------------------------------------------- //
    // ------ Données ---------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //
    int lion_vivant = 20;
    int gazelle_vivante = 20;
    int animaux_mort = 0;
    int gazelle_mangees = 0;
    int vegetal_vivant = 10;
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //
    // ------------------------------------------------------------------------------------------- //

};

#endif
