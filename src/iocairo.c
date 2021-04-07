/**
 * \file iocairo.c
 * \brief Programme de gestion console et programme principale de gestion du jeu
 * \author DONICZKA Quentin
 * \date 17/10/2020
 */

#include "iocairo.h"



void affiche_grille(cairo_surface_t *surface,grille g,int* temps,int* choix_cyclique,int *vieillissement,int* oscillation,int* debut,int* periode)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
    char temps_string[10];
	char debut_string[10];
	char periode_string[10];

	sprintf(temps_string,"%d",*temps);
	sprintf(debut_string,"%d",*debut);
	sprintf(periode_string,"%d",*periode);
	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);
	
	// // line
	// cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	// cairo_move_to (cr, 10.0, 50.0);
	// cairo_line_to(cr, 100.0,50.0);
	// cairo_set_line_width (cr, 1);
	// cairo_stroke (cr);

	// filled rectangle
    
    for(int i = 0; i < g.nbl; i++){
        for(int j = 0; j < g.nbc; j++){
            cairo_rectangle(cr,j*60+10,i*60+200,50,50);
            if (g.cellules[i][j]==-1){
                cairo_set_source_rgb (cr, 0.8,0.1,0.1);
            }
            else if (est_vivante(i, j,g)){
                if(*vieillissement){
                    cairo_set_source_rgb (cr,0.505/g.cellules[i][j],0.925/g.cellules[i][j],0.925/g.cellules[i][j]);
                }
                else{
                    cairo_set_source_rgb (cr, 0.505,0.925,0.925);
                }
            }
	        else{
                cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
            }
	        cairo_fill(cr);
            cairo_rectangle(cr,j*60+10,i*60+200,50,50);
            cairo_set_source_rgb (cr, 1, 1, 1);
            cairo_set_line_width (cr, 0.5);
            cairo_stroke (cr);
        }
    }
    cairo_select_font_face(cr,"monospace",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr,18);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,10,20);
	cairo_show_text(cr,"Nombre d'évolution : ");
	cairo_show_text(cr,temps_string);

    cairo_move_to(cr,10,60);
	if(*choix_cyclique)
	{	
		cairo_show_text(cr,"grille cyclique active");
	}
	else
	{
		cairo_show_text(cr,"grille cyclique désactivé");
	}
    cairo_move_to(cr,10,100);
	if(*vieillissement)
	{	
		cairo_show_text(cr,"vieillissement active");
	}
	else
	{
		cairo_show_text(cr,"vieillissement désactivé");
	}
	cairo_move_to(cr,10,140);
	if(*oscillation==-1)
	{	
		cairo_show_text(cr,"'o' pour afficher l'oscillation");
	}
	else if(*oscillation==0)
	{	
		cairo_show_text(cr,"Pas d'oscillation");
	}
	else if(*oscillation==1)
	{	
		cairo_show_text(cr,"début oscillation : ");
		cairo_show_text(cr,debut_string);
		cairo_move_to(cr,10,180);
		cairo_show_text(cr,"periode : ");
		cairo_show_text(cr,periode_string);

	}
	cairo_destroy(cr); // destroy cairo mask
}





void debut_jeu(grille *g, grille *gc,int* temps,int* choix_cyclique,int* vieillissement,int* oscillation){
    	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	int v_periode = 0;
	int v_debut = 0;
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, (g->nbc)*60+10, (g->nbl)*60+200, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), (g->nbc)*60+10, (g->nbl)*60+200);

	// run the event loop
    alloue_grille(g->nbl, g->nbc, gc);
    
	while(1) {
		XNextEvent(dpy, &e);
            if(e.type==Expose && e.xexpose.count<1) {
                affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
            } 
        else if(e.type == ButtonPress){
            if(e.xbutton.button == 1)
            {
                evolue(g,gc,vieillissement);
                (*temps)++;
                affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
            }
            else if(e.xbutton.button == 3){
            	libere_grille(g);
	            libere_grille(gc);
                break;
            }
        }
        else if(e.type==KeyRelease){
                KeySym key;
                key = XkbKeycodeToKeysym(dpy,e.xkey.keycode,0,0);
                switch(key){
                    case XK_v:
                    	change_vieillissement(vieillissement);
                    	affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
                        break;
                    case XK_c:
                   		choix_voisinage_cyclique(choix_cyclique);
                    	affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
                        break;
                    case XK_n:
                    {
						
						cairo_surface_destroy(cs);
						XCloseDisplay(dpy);
                        char grille_txt[100];
				        scanf("%s",grille_txt);
				        FILE* f_grille_txt = NULL;
                        f_grille_txt = fopen(grille_txt, "r");

				        if (f_grille_txt != NULL){
						    libere_grille(g);
						    libere_grille(gc);
							init_grille_from_file(grille_txt, g);
							fclose(f_grille_txt); 
							alloue_grille(g->nbl, g->nbc, gc);
							if(!(dpy=XOpenDisplay(NULL))) {
								fprintf(stderr, "ERROR: Could not open display\n");
								exit(1);
							}	
							win=XCreateSimpleWindow(dpy, rootwin, 1, 1, (g->nbc)*60+10, (g->nbl)*60+200, 0, 
							BlackPixel(dpy, scr), BlackPixel(dpy, scr));					
							XStoreName(dpy, win, "jeu de la vie");
							XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyReleaseMask);
							XMapWindow(dpy, win);
							cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), (g->nbc)*60+10, (g->nbl)*60+200);
							affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
						}
				        else{
						    printf("fichier non trouvé\n");
				        }
						
                    }
                        break;
                    case XK_o:{
						*oscillation = oscillent (*g,&v_periode,&v_debut,*vieillissement,*temps);
						affiche_grille(cs,*g,temps,choix_cyclique,vieillissement,oscillation,&v_debut,&v_periode);
					}

                        break;
                }
            }
            
    }



	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display

}