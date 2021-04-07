/**
 * \file grille.h
 * \brief Toutes les entêtes de fonctions en rapport avec la grille du jeu de la vie.
 * \author DONICZKA quentin
 * \date 17/10/2020
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * \brief Structure grille
 * \param nbl : nombre de ligne de la grille.
 * \param nbc : nombre de colone de la grille.
 * \param cellules : cellule de notre grille.
 * grille est la structure de gestion de la grille.
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * \fn void alloue_grille (int l, int c, grille* g)
 * \brief alloue une grille pointee par g de taille l*c
 * \param l nombre de ligne de la grille.
 * \param c nombre de colone de la grille.
 * \param g pointeur vers la grille
 */
void alloue_grille (int l, int c, grille* g);

/**
 * \fn void libere_grille (grille* g)
 * \brief libere la grille pointee par g
 * \param g pointeur vers la grille
 */
void libere_grille (grille* g);

/**
 * \fn void init_grille_from_file (char * filename, grille* g)
 * \brief alloue et initalise la grille g à partir d'un fichier
 * \param filename chaine de caractere representant le chemin absolu ou relatif du fichier source de la grille
 * \param g pointeur vers la grille
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * \fn static inline void set_vivante(int i, int j, grille g)
 * \brief rend vivante la cellule (i,j) de la grille g
 * \param i ligne de la cellule
 * \param j colone de la cellule
 * \param g grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \fn static inline void set_invivable(int i, int j, grille g)
 * \brief rend invivable la cellule (i,j) de la grille g
 * \param i ligne de la cellule
 * \param j colone de la cellule
 * \param g grille
 */
static inline void set_invivable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * \fn static inline void set_morte(int i, int j, grille g)
 * \brief rend morte la cellule (i,j) de la grille g
 * \param i ligne de la cellule
 * \param j colone de la cellule
 * \param g grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
/**
 * \fn static inline int est_vivante(int i, int j, grille g)
 * \brief teste si la cellule (i,j) de la grille g est vivante
 * \param i ligne de la cellule
 * \param j colone de la cellule
 * \param g grille
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/**
 * \fn void copie_grille (grille gs, grille gd)
 * \brief recopie gs dans gd (sans allocation)
 * \param gs grille a copier
 * \param gd grille copiee
 */
void copie_grille (grille gs, grille gd);
#endif
