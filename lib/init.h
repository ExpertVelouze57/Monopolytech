#ifndef LIB_INIT_H_
#define LIB_INIT_H_

#include "struct.h"


PLATEAU *init_plateau(); /*permet de construire la structure du plateau en mémoire et de l'initialiser*/

PLATEAU *charger_sauvegarde(); /*permet de construire la structure du plateau en mémoire et de l'initialiser a partir de la sauvegarde*/

int joueur_courant_sauv(); /*lire le joueur courant d'apres la sauvegarde (entre 0 et 3)*/

int parc_gratuit_sauv(); /*lire la valeur du parc gratuit d'apres la sauvegarde */

int tete_file_sauv(); /*lire la valeur de la tete de la file d'apres la sauvegarde */

void sauvegarder(int joueur_courant, PLATEAU *plateau, int parc_gratuit, int tete); /*permet de sauvegarder le plateau*/

void lire_joueur(char *dest, int n); /* permet de lire les infos d'un joueur dans le fichier */

void lire_nom(char *dest, int n); /* permet de lire le nom d'un joueur dans le fichier */

COULEUR lire_type_terrain(int n); /* lit la couleur du terrain dans le fichier */

void lire_terrain(int *tab, int n); /* permet de lire les infos d'un terrain dans le fichier */

void free_plateau(PLATEAU *plateau); /* permet de liberer l'epace memoire du plateau */

void changer_nom_joueur(int joueur, char *nom); /*changer le nom d'un joueur dans le fichier init.txt*/


#endif /* LIB_INIT_H_ */
