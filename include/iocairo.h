/**
 * \file iocairo.h
 * \brief Fichier de gestion console du jeu de la vie
 * \author DONICZKA Quentin
 * \version 1.3.4
 * \date 16/10/2020
 *
 * Gestion de la console du jeu de la vie
 */
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>
#include <unistd.h>



#ifndef __IO_H
#define __IO_H

#define SIZEX 100
#define SIZEY 100

/**
 * \fn void debut_jeu(grille *g, grille *gc,int* temps)
 * \brief debute le jeu
 * \param g pointeur sur grille
 * \param gc pointeur sur grille
 * \param temps pointeur vers le nombre d'evolution de la grille
 * \param choix_cyclique pointeur vers le choix de l'afficahge cylcique ou non
 * \param vieillissement pointeur vers le choix du veillissement ou non
 * \param oscillation pointeur vers le choix de l'affichage de l'oscillation
 * \param debut pointeur vers l'entier stockant le début de l'oscillation
 * \param periode pointeur vers l'entier stockant la periode de l'oscillation
 */
void affiche_grille(cairo_surface_t *surface,grille g,int* temps,int* choix_cyclique,int *vieillissement,int* oscillation,int* debut,int* periode);
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
#endif