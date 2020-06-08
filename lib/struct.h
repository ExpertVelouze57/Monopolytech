#ifndef LIB_STRUCT_H_
#define LIB_STRUCT_H_

typedef enum {MARRON, CYAN, MAGENTA, ORANGE, ROUGE, JAUNE, VERT, BLEU, GARES, COMPAGNIES, AUCUN} COULEUR;

typedef struct loyer {
	int nu; /*si gares : 0						/si compagnies : 0										*/
	int m1; /*si gares : loyer avec 1 gare		/si compagnies : coeff loyer avec 1 compagnie (*4)		*/
	int m2; /*si gares : loyer avec 2 gares		/si compagnies : coeff loyer avec 2 compagnies (*10)	*/
	int m3; /*si gares : loyer avec 3 gares		/si compagnies : 0										*/
	int m4; /*si gares : loyer avec 4 gares		/si compagnies : 0										*/
	int H; 	/*si gares : 0						/si compagnies : 0										*/
} LOYER;

typedef struct terrain {
	char nom[20];
	COULEUR couleur; /*OU int couleur; (de 0 à x dans l'ordre croissant des prix)*/
	int prix;
	int prix_batiment; /*0 si terrain sans maison*/
	LOYER loyer;
	int hypotheque;

	int proprietaire; /*0 à 3 -> ORDRE ; -1 si terrain libre*/
	int nb_maison; /*0 si vide, 1..., 5 si hotel ; -1 si hypotheque*/
} TERRAIN;

typedef struct terrain_joueur {
	int nb_terrain;
	int terr_complet[10]; /*1 si terrain complet ; 0 sinon*/
	TERRAIN *T[10][4]; /*10 pour les 10 categories COULEUR ; et 4 pour 4 terrains max par categorie (4 pour les gares)*/
} TERRAIN_J; /*terrain d'un joueur*/

typedef struct carte_spe {
	int sortie_prison; /*0 ou 1*/
	/*autre ?*/
} CARTE_SPE;

typedef struct joueur {
	char nom[20];
	int position; /*case de 1 a 40*/
	int compte;
	TERRAIN_J terrains;
	CARTE_SPE carte_spe;
} JOUEUR;

typedef struct case_plateau {
	char nom[20];
	TERRAIN *terrain; /*terrain associe à la case ; NULL si different de terrain (case chance, etc)*/
	int joueur[4]; /*0 si joueur non present sur la case, 1 sinon -> respecter l'ORDRE*/
	struct case_plateau *suivante;
	struct case_plateau *precedente;
} CASE;

typedef struct plateau {
	int taille; /*40*/
	JOUEUR *joueurs[4]; /*definition des joueurs -> ORDRE de 0 à 3*/
	int present[4]; /*0 si absent ; 1 sinon*/
	int prison[4]; /*1 si en prison ; 0 sinon*/
	CASE *case_depart; /*pointeur sur la CASE case depart*/
} PLATEAU;


#endif /* LIB_STRUCT_H_ */
