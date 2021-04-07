/**
 * \file main.c
 * \brief Fichier main du jeu de la vie
 * \author DONICZKA Quentin
 * \date 17/10/2020
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"



int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}
	int tem_evo = 0;

	int verif_cyclique = 0;

	int vieillissement = 0;
	
	int oscillation = -1;

	grille g, gc;
	choix_voisinage_cyclique(&verif_cyclique);
	init_grille_from_file(argv[1],&g);
	debut_jeu(&g, &gc,&tem_evo,&verif_cyclique,&vieillissement,&oscillation);
	return 0;
}
