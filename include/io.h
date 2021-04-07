/**
 * \file io.h
 * \brief Fichier de gestion console du jeu de la vie
 * \author DONICZKA Quentin
 * \version 1.3.4
 * \date 16/10/2020
 *
 * Gestion de la console du jeu de la vie
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <unistd.h>
#include "grille.h"
#include "jeu.h"

/**
 * \fn void affiche_trait (int c)
 * \brief affichage d'un trait horizontal
 * \param c position de l'extrait a afficher
 */
void affiche_trait (int c);
/**
 * \fn void affiche_ligne (int c, int* ligne)
 * \brief affichage d'une ligne de la grille
 * \param c position de la ligne a afficher
 * \param ligne chaine de caractere a afficher
 * \param vieillissement chaine de caractere a afficher
 */
void affiche_ligne(int c, int* ligne,int* vieillissement);
/**
 * \fn void affiche_grille (grille g,int temps);
 * \brief affiche toute la grille
 * \param g grille
 * \param temps temps d'evolution de la grille
 * \param choix_cyclique pointeur sur le choix de l'afficahge cyclique ou non
 */
void affiche_grille(grille g,int* temps,int* choix_cyclique,int *vieillissement,int* oscillation,int* debut,int* periode);

/**
 * \fn void efface_grille (grille g)
 * \brief effacement d'une grille
 * \param g grille
 */
void efface_grille(grille g);

/**
 * \fn void debut_jeu(grille *g, grille *gc,int* temps)
 * \brief debute le jeu
 * \param g pointeur sur grille
 * \param gc pointeur sur grille
 * \param temps pointeur vers le nombre d'evolution de la grille
 * \param choix_cyclique pointeur vers le choix de l'afficahge cylcique ou non
 * \param vieillissement pointeur vers le choix du veillissement ou non
 * \param oscillation pour connaitre l'oscillation
 */
void debut_jeu(grille *g, grille *gc,int* temps,int* choix_cyclique,int* vieillissement,int* oscillation);

/**
 * \fn void efface_console()
 * \brief efface toute la console grace a un code d'echappement ANSI
 */
void efface_console();

#endif
