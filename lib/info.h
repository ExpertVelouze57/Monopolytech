#ifndef INFO_H
#define INFO_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "interface_graphique.h"

#define POLICE "police/arial/arial_narrow_7.ttf"
#define POLICE_lb 	"police/liberation/LiberationSans-Bold.ttf"

#define buton  		"images_bmp/bouton.bmp"

#define	c1			"images_bmp/cone_1.bmp"
#define	c2			"images_bmp/cone_2.bmp"
#define	c3			"images_bmp/cone_3.bmp"

#define	ci1			"images_bmp/cone_1_i.bmp"
#define	ci2			"images_bmp/cone_2_i.bmp"
#define	ci3			"images_bmp/cone_3_i.bmp"


/***Fonction qui crée une fenetre indiquant au joueur courant qu'il a perdu (=plus d'argent, plus de terrain,...)***/
void perdu(PLATEAU *plateau, int joueur);

/*Fonction qui indique combien le joueur (joueur_courant) doit payer selon la case sur laquelle il se trouve (position) */
void info_payer(PLATEAU *plateau, int joueur_courant , int position);

/* Fonction d'affichage du joueur gagnant */
void victoire(PLATEAU *plateau, int joueur);

/* Fonction qui demande a l'utilisateur si il veut quitter sans sauvegarder */
int quitter_sauve();

#endif