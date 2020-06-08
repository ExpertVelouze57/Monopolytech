#ifndef INIT_JOUEUR
#define INIT_JOUEUR

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define POLICE_ad "police/arial/arial_narrow_7.ttf"
#define POLICE_lb "police/liberation/LiberationSans-Bold.ttf"
#define fond_pseudo     "images_bmp/fond_texte_joueur_non_selec.bmp"
#define fond_pseudo_s   "images_bmp/fond_texte_joueur_selec.bmp"
#define buton           "images_bmp/bouton.bmp"
#define Bonhomme_n      "images_bmp/bonhomme.bmp"
#define Bonhomme_i      "images_bmp/bonhomme_inverse.bmp"
#define des_n           "images_bmp/de_jouer.bmp"
#define des_i           "images_bmp/de_jouer_inverse.bmp"

#define TAILLE_NOM_JOUEUR 15


/*fct qui récuperer les noms et les donnees dans le fichier, -1 si le programme doit quitter*/
int recuperation_stokage_noms();

/*fct qui indique si 2 chaine sont les mêmes, 1 si identique*/
int meme(char *nom1,char *nom2);

/*recuperation du texte, ? si touche suppr*/
char recuperation_texte(SDL_Event event);

/*Fct qui remplace une chaine vide par joueur_X*/
void chaine_non_vide(char* pseudo, int i);

/*permet d'ajouter ou d'enlever des caractères a partir de recuperation_texte*/
void modification_chaine(char *pseudo, char c);

/*fct qui configure un SDL_Rect avec x et y*/
void creation_pos(SDL_Rect *Position, int x,int y);

/*Fct qui modifie les pseudos pour qu'il ne soit pas identique ou vide*/
void verification_chaine_id(char Noms_joueurs[][TAILLE_NOM_JOUEUR]);

/*fct principale qui lance la fenetre graphique et récupére les noms des 4 joueurs*/
int initialisation_nom_joueurs(char Noms_joueurs[][TAILLE_NOM_JOUEUR]);

/*fct qui verifie si le click de la souris est dans la zone definie*/
int verification_zone(SDL_Event *event, int position_x, int position_y, int largeur, int longueur);

/*Fct qui indique quelle zone notable de la fenetre est selectionée*/
int traitement_click_souris(SDL_Event *event,SDL_Rect P_J1, SDL_Rect P_J2, SDL_Rect P_J3, SDL_Rect P_J4, SDL_Rect P_buton_V);




#endif