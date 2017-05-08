// -------------------------------------------------------------------------------------------- //
// ----- Fichier      : Simulation.hpp                                                    ----- //
// ----- Type         : header                                                            ----- //
// ----- Auteur       : Jérémy                                                            ----- //
// ----- Description  : Permet de crée la simulation                                      ----- //
// -------------------------------------------------------------------------------------------- //
#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QRect>
#include <QVector>
#include <cmath>
#include <QSound>

#include "Animal.hpp"
#include "Statistiques.hpp"

#define FREQUENCE_NATURE 200
#define MAX_VEGETAUX 30

class Simulation : public QGraphicsScene {
  Q_OBJECT
  public:
    // Constructeur et Destructeur
    Simulation(Statistiques* stats, QObject *parent = 0);
    ~Simulation(){};

    // Getters
    QPixmap getImageMort();
    int getLion();
    int getGazelle();
    int getMort();

    // Setters
    void setLion(int l);
    void setGazelle(int g);
    void setMort(int m);

    // Retourne les positions des bordures du terrain de la simulation
    int borderLeft();
    int borderRight();
    int borderTop();
    int borderBottom();

    // ----- Méthodes --------------------------------------------------------------------------- //

    // Fonction qui efface les animaux et le vecteur d'animaux
    // Réinitialise également les données
    void terminer();
    // Peuple le monde
    void peuplement();
    // Fait naitre lion / gazelle si leurs energie augmente
    void naissance(char type);
    // Trouve l'animal le plus proche
    int plus_proche(int a);
    // Trouve la meilleur direction pour le déplacement entre 2 animaux
    int deplacement_intelligent(int a1, int a2);
    void affrontement(int animal); // Affonrtement entre lion et gazelle
    void nature(int indice); // Fait naître des plantes de temps en temps
    // ------------------------------------------------------------------------------------------ //
  signals:
    // Emet toutes les données utilisées par le camembert
    void signal_valeurs(int, int, int, int, int);

  public slots:
    // ----- Modifie les différentes données au changement des sliders -------------------------- //
    void slot_nb_animaux(int);
    void slot_setProportion(int);
    void slot_vitesse(int);
    void slot_setEnergie(int);
    void slot_setTailleX(int);
    void slot_setTailleY(int);
    // ------------------------------------------------------------------------------------------ //

    // Démarre / Arrête la simulation
    void slot_simulation();

    void update(); // Passe un tour

  private:
    QGraphicsRectItem *terrain; // Terrain de la simulation
    Statistiques* statsWindow; // Fenêtre de stats

    QTimer *timer; // Timer

    // Vecteur d'animaux
    QVector<Animal*> vect_animaux;

    // Booléan : Savoir si la simulation est active
    bool simu_en_cours = false;

    // Taille de la simulation
    int tailleX = 0, tailleY = 0;

    int nb_animaux = 50; // Nombre d'animaux initial
    int proportion = 2; // Proportion par défaut
    int vitesse = 20; // Vitesse du timer
    int energie = 200; // Energie initiale

    int sens = -1; // Direction pour bouger les animaux
    int nature_naissance = 0; // Compteur contrôle des naissances

    // ----- Données ---------------------------------------------------------------------------- //
    int lion_vivant = 0, gazelle_vivante = 0, vegetal_vivant = 0;
    int animaux_mort = 0, gazelle_mange = 0;
    // ------------------------------------------------------------------------------------------ //

    // ----- Les différentes images ------------------------------------------------------------- //
    QPixmap lion;
    QPixmap gazelle;
    QPixmap vegetal;
    QPixmap gigot;
    QPixmap tombe;
    // ------------------------------------------------------------------------------------------ //

    QSound* musique; // Musique
};

#endif
