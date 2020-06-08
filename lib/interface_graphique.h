#ifndef INTERFACE_GRAPHIQUE_H
#define INTERFACE_GRAPHIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "struct.h"
#include "init.h"
#include "fct_elem.h"
#include "ordre_depart.h"
#include "fct.h"
#include "init_joueur.h"
#include "fenetre_tt_tour.h"
#include "aide_graphique.h"
#include "joueur_ruine.h"
#include "choix_prison.h"
#include "info.h"



#define MAX 6
#define MIN 1

/* fonction qui attend un evenement (appui sur bouton,...) */
int pause(SDL_Surface *ecran, int joueur_courant, PLATEAU *plateau, int *parc_gratuit, int tete);

/* permet de colorer un pixel de l'ecran */
void SDL_PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel);

/* permet de tracer une ligne a l'ecran */
void Line(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur);

/* affichage des 4 cases recapitulatives au centre du plateau */
void cases4_joueurs(int joueur, SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, SDL_Surface *texte, PLATEAU *plateau);

/* affichage des lignes principales du plateau */
void affichage_lignes(SDL_Surface *ecran);

/* permet d'affiche les cases des rues du plateau */
void affiche_rues(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran);

/* permet de placer le curseur des joueurs sur le plateau */
void placer_joueur(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, int pos, int num, int nb);

/* permet d'afficher les maisons presentes sur les rues du plateau */
void placer_maison(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, int pos, int nb);

/* permet l'affichage des dés sur le plateau */
void lance_des(SDL_Surface *ecran, int *a, int*b, SDL_Rect posdes1, SDL_Rect posdes2);

/* fonction pour l'appui sur le bouton sauvegarde */
int traitement_bouton_sauvegarde(SDL_Event *event);

/* renvoie 2 nombres aleatoires dans a et b */
void nb_alea(int *des1, int *des2);

/* permet de renvoyer dans dest le nom du fichier du dés correspondant a num */
void choix_des(char *dest, int num);

/* affichage des textes de base de l'ecran de jeu */
void texte_base(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte);

/* affiche le nombre de proprietes sur la droite de l'ecran pour chaque couleur */
void ecrire_propriete(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int *tab);

/* affiche les informations relatives au joueur sur la droite de l'ecran */
void infos_joueur(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int j);

/* affiche le proprietaire de chaque terrain */
void affiche_proprietaire(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *rectangle, PLATEAU *plateau, int terrain);

/* fonction pour l'appui sur les boutons de l'ecran de demarrage */
int traitement_bouton_demarrage(SDL_Event *event, SDL_Rect position1, SDL_Rect position2, SDL_Rect position3, SDL_Surface *texte1, SDL_Surface *texte2, SDL_Surface *texte3);

/* fonction pour le deplacement de la souris sur l'ecran de demarrage */
int traitement_deplacement(SDL_Event *event, SDL_Rect position1, SDL_Rect position2, SDL_Rect position3, SDL_Surface *texte1, SDL_Surface *texte2, SDL_Surface *texte3);

/* teste si le mot contient un "_" ou non, renvoie 1 si oui et 0 sinon */
int contient_tiret(char *mot);

/* separe mot en 2 si besoin au niveau du "_" */
void gestion_tiret(char *mot, char *mot2);

/* affiche les noms des rues sur le plateau */
void ecrire_nom_rue(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, PLATEAU *plateau, int rue, TTF_Font *police_p, TTF_Font *police8, TTF_Font *police9, TTF_Font *police10);

/* affiche l'ecran de demarrage */
int affiche_ecran_demarrage();

/* affiche l'argent de open_source au centre du plateau */
void affiche_argent_parc(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, int *parc_gratuit);

/* affichage des infos de la case sur laquelle le joueur est */
void affiche_infos_case(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int rue, int joueur);

/* permet d'afficher le plateau de jeu */
int affiche_plateau(int joueur, PLATEAU *plateau, int *parc_gratuit, int lancer, int *a, int *b, int tete);

/* affiche l'ecran de lancer de dés pour l'ordre de jeu */
int affiche_lancer_de(char nom[][15]);

/* renvoie differents messages d'erreur en fonction de e */
void erreur(int e);

/* demande a l'utilisateur si il veut acheter le terrain, renvoie 1 si oui et 0 sinon */
int choix_achat_terrain(PLATEAU *plateau, int pos, int joueur_courant);

/* demande a l'utilisateur ce qu'il veut vendre si il est ruiné, (1) maisons, (2) terrain, (3) carte sortie prison */
int si_joueur_ruine();

/* affiche l'action a effectuer en fonction de action */
void action_carte(int action, int somme, char *t);

/* affichage pour demander a l'utilisateur si il veut racheter un terrain hypothequé, renvoie 1 si oui et 0 sinon */
int rachat_hypotheque(PLATEAU *plateau, int pos, int joueur_courant);

#endif