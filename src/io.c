/**
 * \file io.c
 * \brief Programme de gestion console et programme principale de gestion du jeu
 * \author DONICZKA Quentin
 * \date 17/10/2020
 */
#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne(int c, int* ligne,int* vieillissement){
	int i;
	if (*vieillissement==0){
		for (i=0; i<c; ++i)
			if (ligne[i] == -1)	printf ("| X ");
			else if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
			
	}
	else{
		for (i=0; i<c; ++i)
			if (ligne[i] == -1)	printf ("| X "); 
			else if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]);
	}
	printf("|\n");
	return;
}

void affiche_grille(grille g,int* temps,int* choix_cyclique,int *vieillissement,int* oscillation,int* debut,int* periode){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("nombre d'evolution : %d    ",*temps);
	if(*choix_cyclique==1) printf("grille cyclique: Oui    "); 
	else printf("grille cyclique: Non    ");
	if(*vieillissement==1) printf("vieillissement: Oui    "); 
	else printf("vieillissement: Non    ");
	if(*oscillation==-1) printf("\n\n'o' pour afficher l'oscillation\n");
	else if(*oscillation==0) printf("\n\npas d'oscillation\n");
	else printf("\n\ndebut oscillation : %d\t\tperiode : %d\n",*debut,*periode);

	(*temps)++;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i],vieillissement);
		affiche_trait(c);
	}	
	printf("\n");


	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 9); 
}

void efface_console(){
  printf("\e[H\e[2J");
}

void debut_jeu(grille *g, grille *gc,int* temps,int* choix_cyclique,int* vieillissement,int* oscillation){
	int v_periode = 0;
	int v_debut = 0;
	alloue_grille(g->nbl, g->nbc, gc);
	efface_console();
	affiche_grille(*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case 'v':
			{	
				efface_console();
				change_vieillissement(vieillissement);
				printf("\e[F");
				break;

			}
			case 'o':
			{	
				efface_console();
				*oscillation = oscillent (*g,&v_periode,&v_debut,*vieillissement,*temps);
				printf("\e[F");
				break;

			}
			case 'c':
			{	
				efface_console();
				choix_voisinage_cyclique(choix_cyclique);
				printf("\e[F");
				break;
			}
			case 'n':
			{
                char grille_txt[100];
				scanf("%s",grille_txt);

				FILE* f_grille_txt = NULL;
                f_grille_txt = fopen(grille_txt, "r");

				if (f_grille_txt != NULL){
						efface_console();
						libere_grille(g);
						libere_grille(gc);
						init_grille_from_file(grille_txt, g);
						alloue_grille(g->nbl, g->nbc, gc);
						(*temps)=0;
						affiche_grille(*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
						fclose(f_grille_txt);
				}
				else{
						efface_console();
						printf("fichier non trouvé\n");
						sleep(2);
						efface_console();
						(*temps)--;
						affiche_grille(*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
				}
			do{
			c = getchar();
			}while(c != '\n');

			break;
		}

			case '\n':
			{ // touche "entree" pour évoluer
				evolue(g,gc,vieillissement);
				efface_grille(*g);
				affiche_grille(*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	libere_grille(g);
	libere_grille(gc);
	return;	
}
