#ifndef LIB_FCT_H_
#define LIB_FCT_H_

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

#define MAX 6
#define MIN 1
#define max 31

typedef int ElemFile;

typedef struct {
    int taille;
    int tete;
    ElemFile T[max];
} File;


/*Fonction qui ajoute la valeur du parc gratuit sur le compte du joueur, puis remet parc gratuit à 0*/
void case_parc_gratuit(int joueur, int *parc_gratuit, PLATEAU *plateau);

/*Fonction utilisée lorsqu'un joueur s'arrête sur la case départ, il recoit 400pp*/
void case_depart(int joueur, PLATEAU *plateau);

/*enlève 100 au joueur courant, +100 parc gratuit*/
void taxes(int joueur, int *parc_gratuit, PLATEAU *plateau);

/*enlève 200 au joueur courant, +200 parc gratuit*/
void impots_sur_revenu(int joueur, int *parc_gratuit, PLATEAU *plateau);

/*fct qui envoie le joueur en prison, et donc modifie la variable associé*/
void allez_en_prison(int joueur, PLATEAU *plateau);


void nb_alea(int *a, int *b);

/*renvoie 0 si le joueur peut encore gagner de l'argent en vendant qqc, ou 1 sinon*/
int a_sec(int joueur, PLATEAU *plateau);

/*transfert tout les terrains du joueur qui ne peut pas payer au joueur à qui il doit de l'argent*/
void transfert_terrains(int joueur, int joueur_qui_gagne, PLATEAU *plateau);

/*transfert tout les terrains du joueur qui ne peut pas payer à la banque lorsqu'il doit de l'argent à la banque (case impôts par exemple)*/
void transfert_terrains_banque(int joueur, PLATEAU *plateau);

/*fct qui réportorie tout les effets des cases chances et effectue les modification nécessaires*/
void chance(int joueur, int *parc_gratuit, int *nouvel_effet, PLATEAU *plateau, File *F);


void init_file(File *F);


void afficher_file(File F);


int defile(File *F);

/* renvoie 1 si tous les terrains ont ete achetes, -1 sinon */
int tout_achete(PLATEAU *plateau);


#endif /* LIB_FCT_H_ */
