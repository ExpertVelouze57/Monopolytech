#ifndef LIB_JOUEUR_RUINE_H
#define LIB_JOUEUR_RUINE_H

#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "interface_graphique.h"


#define POLICE "police/arial/arial_narrow_7.ttf"
#define buton "images_bmp/bouton.bmp"


/*fct qui affiche que le joueur n'a pas de carte sortie de prison*/
int pas_de_carte(); 

/*Demande la validation (retour=1) ou le refus (retour=0) pour vendre la carte*/
int vendre_carte();

/*listing et selection d'une terrain apartenant au joueur et ayant une maison"joueur_choisie"*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain => confirmation =-1*/
int choix_proprietes_maison(PLATEAU *plateau, int joueur_choisie);

/*Listing du nombre de maison(s) et hotel du terrain choisit "terrain_choi" du joueur "joueur_courant"*/
int choix_maisons(PLATEAU *plateau, int joueur_courant, int terrain_choi);

/*fct qui demande confirmatuon la proposition pour la vente "de nb_mai" maisons, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int identification_maison(int val_retour, int joueur_courant);

/*Fonction qui retourne le nombre de maison a vendre en fonction du bouton sur lequel on a appuyer "val_retour"*/
int choix_proprietes_hypotheque(PLATEAU *plateau, int joueur_choisie);

/*/*listing et selection d'une terrain apartenant au joueur et pouvant etre hypothequer*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain => confirmation =-1*/
int confirmation_hypotheque(PLATEAU *plateau, int joueur, int terrain, int prix);

/*fct qui demande confirmatuon la proposition pour l'achat d'un terraint T, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int confirmation_maison(PLATEAU *plateau, int nb_mai, int terrain, int prix);


#endif