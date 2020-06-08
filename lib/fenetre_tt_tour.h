/******************************************************************************************/
/*																						  */
/*        Contenu du fichier: fonction graphique choix joueur à chaque tour	     		  */
/*05/05/2020																			  */
/*																						  */
/******************************************************************************************/
#ifndef FENETRE_TT_TOUR
#define FENETRE_TT_TOUR

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "aide_graphique.h"
#include "struct.h"
#include "fct_elem.h"

#define POLICE "police/arial/arial_narrow_7.ttf"

#define fond_pseudo     "images_bmp/fond_texte_joueur_non_selec.bmp"
#define fond_pseudo_s   "images_bmp/fond_texte_joueur_selec.bmp"
#define buton           "images_bmp/bouton.bmp"


/*fct qui permets a l'utilisateur de choisir entre lancer les des(3), acheter une maison(2) ou proposer d'acheter u  terraint a un autre joueur(1)*/
int debut_tour();

/********************************/
/*fct proposition achat terrain**/
/********************************/
/*aucun retour, les données sont placer dans le 4 dernier paramaetre joueur(0->3), terrain(1->40), prix et validation(1 ok, -1pas ok)*/
void proposition_achat_terrain(PLATEAU *plateau,int joueur_courant,int *joueur, int *terrain, int *prix, int* validation);

/*fct qui permets de choisir un joueur different du joueur courant*/
int choix_joueur(PLATEAU *plateau, int joueur_courant);

/*listing et selection d'une terrain apartenant au joueur "joueur_choisie"*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain confirmation =-1*/
int choix_proprietes(PLATEAU *plateau, int joueur_choisie);

/*fct qui renvoie le prix indiquer*/
int selection_prix(PLATEAU *plateau, int joueur_courant);

/*fct qui demande confirmatuon la proposition pour l'achat d'un terraint T, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int confirmation_proposition(PLATEAU *plateau, int joueur, int terrain, int prix);
													 
/********************************/
/*fct proposition achat maison*/
/********************************/

/*renvoie 1 si achat batiment sur le terrain*/
int achat_maison(PLATEAU *plateau,int joueur_courant,int *terrain);

/*demande confirmation de l'achat d'un batiemtn sur le terrain 1 si ok -1 sinon*/
int analyse_achat_maison(TERRAIN terrain,PLATEAU *plateau,int joueur_courant);

/* enumeration de toutes les proprietes eligibles a l'ajout de maisons
renvoie le numero du terrain ou -1*/
int choix_proprietes_maison_achat(PLATEAU *plateau, int joueur_choisie);


/****************/
/*fct utilitaire*/
/****************/

/*fct qui retourn le numero du joueur en fct du bouton slectioner 0->3*/
int identification_numero_joueur(int val_retour, int joueur_courant, PLATEAU *plateau);

/*fct qui modifier la chaine de caractère prix a chaque ajout de chiffre(clavier)*/
void modification_prix(SDL_Event event,char *prix);


#endif

