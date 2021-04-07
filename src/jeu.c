/**
 * \file jeu.c
 * \brief Programme de gestion du voisinage et d'évoution de grille
 * \author DONICZKA Quentin
 * \date 17/10/2020
 */
#include "jeu.h"
int (*compte_voisin_vivant) (int, int, grille);
int choix_vieillissement = 0;

void choix_voisinage_cyclique(int* choix_cyclique){
	if((*choix_cyclique)==0){
		compte_voisin_vivant=compte_voisins_cyclique;
		(*choix_cyclique)++;
	}
	else{
		compte_voisin_vivant=compte_voisins_non_cyclique;
		(*choix_cyclique)--;
	}
}

int compte_voisins_cyclique(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	for (int a=i-1; a<=(i+1); a++){
		for (int b=j-1; b<=(j+1); b++){
			if (!(a==i && b==j)) v+= est_vivante(modulo(a,l),modulo(b,c),g);
		}
	}
	return v; 
}

int compte_voisins_non_cyclique(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	for (int a=i-1; a<=(i+1); a++){
		for (int b=j-1; b<=(j+1); b++){
			if((a>=0 && a<l && b>=0 && b<c) && !(a==i && b==j)) v+= est_vivante(a,b,g);
		}
	}
	return v; 
}

void evolue(grille *g, grille *gc,int *vieillissement){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (g->cellules[i][j] != -1){
				v = (*compte_voisin_vivant)(i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if (*vieillissement==1) f_vieillissement(i,j,*g);
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}
void f_vieillissement(int i,int j, grille g){
	g.cellules[i][j]++;
	if(g.cellules[i][j]>8) set_morte(i,j,g);
}
void change_vieillissement(int *choix_vieillissement){
	if(*choix_vieillissement == 0){
		*choix_vieillissement = 1;
	}
	else *choix_vieillissement = 0;
}

int oscillent (grille g,int* periode, int* debut,int vieillissement,int temps){
	char * grillemort = calloc(1,g.nbl*g.nbc+1);
	memset(grillemort,'0',g.nbl*g.nbc);
	grille g1,g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	tab_osci tab;
	tab.taille=0;
	tab.chargrille=calloc(1,1);
	stringGrille(g1,&tab);
	while(strcmp(tab.chargrille[tab.taille++],grillemort)){
		evolue(&g1,&g2,&vieillissement);
		stringGrille(g1,&tab);
		
		for(int i = tab.taille-1;i>=0 ;i--){
			if (!strcmp(tab.chargrille[i],tab.chargrille[tab.taille]))
			{	
				*periode=tab.taille-i;
				*debut=i+temps;
				free(grillemort);
				libere_grille(&g1);
				libere_grille(&g2);
				freetabosci(tab);
				return 1;
			}
			
		}
		
		
	}


	free(grillemort);
	libere_grille(&g1);
	libere_grille(&g2);
	freetabosci(tab);
	return 0;
}
void stringGrille(grille g,tab_osci *tab){
	char ** pointeur=malloc(sizeof(char *)*(tab->taille+1));
	memcpy(pointeur,tab->chargrille,sizeof(char *)*(tab->taille));
	free(tab->chargrille);
	tab->chargrille=pointeur;
	tab->chargrille[tab->taille] = calloc(1,1);
	for (int i=0; i<g.nbl; ++i){
		for (int j=0; j<g.nbc; ++j){
			asprintf(&tab->chargrille[tab->taille],"%s%c",tab->chargrille[tab->taille],g.cellules[i][j]<=0?'0':'0'+g.cellules[i][j]);
		} 
	}
} 
void freetabosci(tab_osci tab){
	for(int i = 0; i<tab.taille ;i++){
		free(tab.chargrille[i]);
	}
	free(tab.chargrille);
}