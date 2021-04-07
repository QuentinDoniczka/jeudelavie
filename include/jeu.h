/**
 * \file jeu.h
 * \brief Toutes les entêtes de fonctions en rapport avec la gestion du voisinage et de l'évolution de la grille.
 * \author DONICZKA quentin
 * \date 17/10/2020
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#include "string.h"

/**
 * \fn static inline int modulo(int i, int m)
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \param i
 * \param m
 * \return la valeur rendant correcte le traitement des bords cycliques
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \fn compte_voisins_cyclique(int i, int j, grille g)
 * \brief compte le nombre de voisins vivants de la cellule (i,j) les bords sont cycliques.
 * \param i ligne de la cellule
 * \param j colonne de la cellule
 * \param g grille
 */
int compte_voisins_cyclique(int i, int j, grille g);
/**
 * \fn compte_voisins_non_cyclique(int i, int j, grille g)
 * \brief compte le nombre de voisins vivants de la cellule (i,j) les bords sont non cycliques.
 * \param i ligne de la cellule
 * \param j colonne de la cellule
 * \param g grille
 */
int compte_voisins_non_cyclique(int i, int j, grille g);
/**
 * \fn void evolue (grille *g, grille *gc)
 * \brief fait évoluer la grille g d'un pas de temps
 * \param g pointeur sur grille initial
 * \param gc pointeur sur grille a la generation suivante
 * \param vieillissement pointeur sur vieillissement
 */
void evolue(grille *g, grille *gc,int *vieillissement);
/**
 * \fn choix_voisinage_cyclique(int* choix_cyclique)
 * \brief switch entre une grille cyclique ou non.
 * \param choix_cyclique pointeur vers la valeur du choix de l'affichage cyclique ou non
 */
void choix_voisinage_cyclique(int* choix_cyclique);
/**
 * \fn vieillissement(int i,int j, grille g)
 * \brief incremente de 1 les cellule vivante qui reste sur la même case après une évolution, et fait mourir les cellule qui on plus de 8 "d'age"
 * \param i ligne de la cellule
 * \param j colonne de la cellule
 * \param g grille
 */
void f_vieillissement(int i,int j, grille g);
/**
 * \fn change_vieillissement()
 * \brief change la valeur de la variable vieillissement a 1 ou 0 selon l'était précédent
 * \param choix_vieillissement pointeur vers la valeur du choix du vieillissement
 */
void change_vieillissement(int *choix_vieillissement);
/**
 * \fn int oscillent (int* periode, int *début)
 * \brief renvois vrai ou faux si grille à une ossciation et si oui modifie dans les deux argument la periode de l'ossiation et le début
 * \param periode pointeur sur periode
 * \param debut pointeur sur début
 * \param vieillissement vieillissement actif ou non
 * \param temps temps de la grille
 */
int oscillent (grille g,int* periode, int* debut,int vieillissement,int temps);

/**
 * \struct tab_osci
 * \brief Structure de string de grille
 * \param taille : taille de notre tableau.
 * \param chargrille : cellule de notre grille.
 */
typedef struct {int taille; char** chargrille;} tab_osci;
/**
 * \fn void freetabosci(tab_osci tab)
 * \brief libère la mémoire de tab de type tab_osci
 * \param tab : tableau a libéré
 */
void freetabosci(tab_osci tab);

/**
 * \fn stringGrille(grille g,tab_osci tab)
 * \brief transforme la grille en string
 * \param g : grille a transformer en string
 * \param tab : tableau pour stocké nos string
 */
void stringGrille(grille g,tab_osci *tab);

#endif
