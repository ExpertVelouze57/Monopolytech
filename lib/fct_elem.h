#ifndef LIB_FCT_ELEM_H_
#define LIB_FCT_ELEM_H_

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"


/*			Seul le pointeur vers le plateau est necessaire               */


/*_______________________________________________________________________________________________________*/
/*LECTURE -> à partir d'un chiffre de 0 à 3 pour le joueur, d'un chiffre de 1 à 40 pour le terrain (case)*/
/*_______________________________________________________________________________________________________*/



void nom_joueur(char *nom, int joueur, PLATEAU *plateau); /*nom d'un joueur*/
/*arg char *nom -> destination*/


int joueur_present(int joueur, PLATEAU *plateau); /*test la presence d'un joueur sur le plateau*/
/*1 si present ; 0 sinon*/


void nom_terrain(char *nom, int terrain, PLATEAU *plateau); /*nom d'un terrain*/
/*arg char *nom -> destination*/


int nb_gares(int joueur, PLATEAU *plateau); /*nombre de gares d'un joueur*/


int nb_compagnies(int joueur, PLATEAU *plateau); /*nombre de compagnies d'un joueur*/


int nb_maisons(int terrain, PLATEAU *plateau); /*nombre de maisons sur un terrain*/


int test_hypotheque(int terrain, PLATEAU *plateau); /*test si le terrain est hypotheque*/
/*1 si terrain hypotheque ; 0 sinon*/


int loyer(int joueur, int terrain, PLATEAU *plateau); /*calcul le loyer qu'un joueur doit payer en fonction de la case sur laquelle il se trouve*/
/*	(cette fonction prend tous les cas possibles en compte)*/


int valeur_hypothequaire(int terrain, PLATEAU *plateau); /*valeur de l'hypotheque d'un terrain*/


int prix_terrain(int terrain, PLATEAU *plateau); /*prix d'un terrain*/


int prix_construction(int terrain, PLATEAU *plateau); /*prix pour construire UN batiment sur un terrain*/


COULEUR type_terrain(int terrain, PLATEAU *plateau); /*type d'un terrain*/
/*	voir typedef enum dans fichier struct.h pour le type COULEUR*/


int nb_terrains_joueur(int joueur, PLATEAU *plateau); /*nombre de terrains que possède un joueur*/


int nb_terrains_complets_joueur(int joueur, PLATEAU *plateau); /*nombre de terrains complets que possede un joueur*/


int compte_joueur(int joueur, PLATEAU *plateau); /*compte en banque d'un joueur*/


int prisonnier(int joueur, PLATEAU *plateau); /*test si un joueur est en prison*/
/*1 si prisonnier ; 0 sinon*/


int sortie_de_prison(int joueur, PLATEAU *plateau); /*test si un joueur possede la carte sortie de prison*/
/*1 si dispo ; 0 sinon*/


int proprietaire_terrain(int terrain, PLATEAU *plateau); /*donne le joueur (0 à 3) proprietaire d'un terrain*/
/*-1 si terrain libre*/

int position_joueur(int joueur, PLATEAU *plateau); /*donne la case sur laquelle le joueur se trouve (de 1 a 40)*/



/*_____________________________________________________________________________________________*/
/*ECRITURE*/
/*_____________________________________________________________________________________________*/


void modif_compte_joueur(int joueur, int val, PLATEAU *plateau); /*remplace le compte du joueur par val*/


void ajout_maison(int terrain, PLATEAU *plateau); /*ajoute une maison d'un terrain (si possible)*/


void vente_maison(int terrain, PLATEAU *plateau); /*retire une maison d'un terrain (si possible)*/


void achat_terrain(int terrain, int joueur, PLATEAU *plateau); /*ajoute un terrain a un joueur si il est libre*/


void vente_terrain(int terrain, int joueur, PLATEAU *plateau); /*libere le terrain d'un joueur si il est occupe mais sans maison*/


void modif_sortie_de_prison(int joueur, PLATEAU *plateau); /*inverse l'etat d'obtention de la carte*/
/*1 si 0 ; 0 si 1*/


void modif_hypotheque(int terrain, PLATEAU *plateau); /*hypotheque ou deshypotheque un terrain (si possible)*/
/*passe à -1 si 0 ; passe a 0 si -1 ; ne fait rien si >= 1*/


void deplacement_joueur (int joueur, int nouvelle_case, PLATEAU *plateau); /*deplace le joueur vers nouvelle_case*/


void virer_joueur(int joueur, PLATEAU *plateau); /*retire un joueur du jeu*/


void etat_prison(int joueur, PLATEAU *plateau); /*place ou retire un joueur de prison*/
/*0 si 1 ; 1 si 0*/



/*_____________________________________________________________________________________________*/
/*FCT SUPPLEM (ne pas utiliser)*/

CASE *ptr_case(int n, PLATEAU *plateau); /*donne le pointeur de la n-ième case (n de 1 à 40)*/

void copie_string(char *src, char *dest); /*copie un chaine de caracteres dans une autre*/

void cat(char *mot1, char *mot2); /*concatene 2 mot*/


#endif /* LIB_FCT_ELEM_H_ */
