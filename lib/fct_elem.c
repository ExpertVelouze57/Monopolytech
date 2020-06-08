#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "fct_elem.h"




/*________________________________________________________________________________________________*/
/*nom d'un joueur, arg char *nom -> destination*/
void nom_joueur(char *nom, int joueur, PLATEAU *plateau) {
	int i;
	for (i=0; i<20; i++)
		nom[i]='\0';
	copie_string(plateau->joueurs[joueur]->nom,nom);
}

/*test la presence d'un joueur sur le plateau, renvoie 1 si present ; 0 sinon*/
int joueur_present(int joueur, PLATEAU *plateau) { /*1 si present ; 0 sinon*/
	return plateau->present[joueur];
}

/*nom d'un terrain, arg char *nom -> destination*/
void nom_terrain(char *nom, int terrain, PLATEAU *plateau) {
	int i;
	for (i=0; i<20; i++)
		nom[i]='\0';
	copie_string(ptr_case(terrain,plateau)->nom,nom);
}

/*nombre de gares d'un joueur*/
int nb_gares(int joueur, PLATEAU *plateau) {
	int cmp=0, i;
	for (i=0; i<4; i++)
		if (plateau->joueurs[joueur]->terrains.T[8][i] != NULL)
			cmp++;
	return cmp;
}

/*nombre de compagnies d'un joueur*/
int nb_compagnies(int joueur, PLATEAU *plateau) {
	int cmp=0, i;
	for (i=0; i<2; i++)
		if (plateau->joueurs[joueur]->terrains.T[9][i] != NULL)
			cmp++;
	return cmp;
}

/*nombre de maisons sur un terrain*/
int nb_maisons(int terrain, PLATEAU *plateau) {
	CASE *ptr;
	ptr=ptr_case(terrain,plateau);
	if (ptr->terrain == NULL) return 0;
	if (ptr->terrain->nb_maison == -1) return 0;
	return ptr->terrain->nb_maison;
}

/*test si le terrain est hypotheque, renvoie 1 si terrain hypotheque ; 0 sinon*/
int test_hypotheque(int terrain, PLATEAU *plateau) { /*1 si terrain hypotheque ; 0 sinon*/
	if (ptr_case(terrain,plateau)->terrain->nb_maison == -1)
		return 1;
	return 0;
}

/*calcul le loyer qu'un joueur doit payer en fonction de la case sur laquelle il se trouve*/
/*	(cette fonction prend tous les cas possibles en compte)*/
int loyer(int joueur, int terrain, PLATEAU *plateau) {
	CASE *ptr;
	ptr=ptr_case(terrain,plateau);
	if (ptr->terrain == NULL) return 0; /*si pas terrain*/
	if (ptr->joueur[joueur] == 0) return 0; /*si joueur pas sur terrain*/
	if (ptr->terrain->nb_maison == -1) return 0; /*si terrain hypotheque*/
	if (ptr->terrain->proprietaire == joueur || ptr->terrain->proprietaire == -1) return 0; /*si joueur est proprietaire*/
	if (ptr->terrain->couleur == GARES) { /*GARES*/
		int nb=nb_gares(ptr->terrain->proprietaire,plateau);
		if (nb == 1) return ptr->terrain->loyer.m1;
		else if (nb == 2) return ptr->terrain->loyer.m2;
		else if (nb == 3) return ptr->terrain->loyer.m3;
		else if (nb == 4) return ptr->terrain->loyer.m4;
		return 0;
	}
	if (ptr->terrain->couleur == COMPAGNIES) { /*COMPAGNIES -> Attention : renvoit le coeff !!!*/
		int nb=nb_compagnies(ptr->terrain->proprietaire,plateau);
		if (nb == 1) return ptr->terrain->loyer.m1;
		if (nb == 2) return ptr->terrain->loyer.m2;
		return 0;
	}
	/*TERRAINS CONSTRUCTIBLES*/
	int nb=ptr->terrain->nb_maison;
	if (nb == 0) { /*Cas du terrain nu*/
		if (plateau->joueurs[ptr->terrain->proprietaire]->terrains.terr_complet[ptr->terrain->couleur] == 1)
			return 2*ptr->terrain->loyer.nu; /*fois 2 si terrain complet*/
		return ptr->terrain->loyer.nu;
	}
	else if (nb == 1) return ptr->terrain->loyer.m1;
	else if (nb == 2) return ptr->terrain->loyer.m2;
	else if (nb == 3) return ptr->terrain->loyer.m3;
	else if (nb == 4) return ptr->terrain->loyer.m4;
	else if (nb == 5) return ptr->terrain->loyer.H;
	return 0;
}

/*valeur de l'hypotheque d'un terrain*/
int valeur_hypothequaire(int terrain, PLATEAU *plateau) {
	return ptr_case(terrain,plateau)->terrain->hypotheque;
}

/*prix d'un terrain*/
int prix_terrain(int terrain, PLATEAU *plateau) {
	return ptr_case(terrain,plateau)->terrain->prix;
}

/*prix pour construire UN batiment sur un terrain*/
int prix_construction(int terrain, PLATEAU *plateau) {
	return ptr_case(terrain,plateau)->terrain->prix_batiment;
}

/*type d'un terrain*/
COULEUR type_terrain(int terrain, PLATEAU *plateau) {
	return ptr_case(terrain,plateau)->terrain->couleur;
}

/*nombre de terrains que possède un joueur*/
int nb_terrains_joueur(int joueur, PLATEAU *plateau) {
	return plateau->joueurs[joueur]->terrains.nb_terrain;
}

/*nombre de terrains complets (toutes les rues d'une couleur) que possede un joueur*/
int nb_terrains_complets_joueur(int joueur, PLATEAU *plateau) {
	int cmp=0, i;
	for (i=0; i<10; i++)
		if (plateau->joueurs[joueur]->terrains.terr_complet[i] == 1)
			cmp++;
	return cmp;
}

/*compte en banque d'un joueur*/
int compte_joueur(int joueur, PLATEAU *plateau) {
	return plateau->joueurs[joueur]->compte;
}

/*test si un joueur est en prison*/
int prisonnier(int joueur, PLATEAU *plateau) { /*1 si prisonnier ; 0 sinon*/
	return plateau->prison[joueur];
}

/*test si un joueur possede la carte sortie de prison, renvoie 1 si carte dispo ; 0 si pas de carte*/
int sortie_de_prison(int joueur, PLATEAU *plateau) { 
	return plateau->joueurs[joueur]->carte_spe.sortie_prison;
}

/*donne le joueur (0 à 3) proprietaire d'un terrain*/
/*-1 si terrain libre*/
int proprietaire_terrain(int terrain, PLATEAU *plateau) { 
	return ptr_case(terrain,plateau)->terrain->proprietaire;
}

/*donne la case sur laquelle le joueur se trouve (de 1 a 40)*/
int position_joueur(int joueur, PLATEAU *plateau) {
	return plateau->joueurs[joueur]->position;
}


/*________________________________________________________________________________________________*/

/*remplace le compte du joueur par val*/
void modif_compte_joueur(int joueur, int val, PLATEAU *plateau) {
	plateau->joueurs[joueur]->compte=val;
}

/*ajoute une maison au terrain*/
void ajout_maison(int terrain, PLATEAU *plateau) { /*+1 si <5 et >-1*/
	if (ptr_case(terrain,plateau)->terrain->nb_maison < 5 && ptr_case(terrain,plateau)->terrain->nb_maison > -1)
		ptr_case(terrain,plateau)->terrain->nb_maison+=1;
}

/*enlève une maison à un terrain*/
void vente_maison(int terrain, PLATEAU *plateau) { /*-1 si <=5 et >0*/
	if (ptr_case(terrain,plateau)->terrain->nb_maison < 6 && ptr_case(terrain,plateau)->terrain->nb_maison > 0)
		ptr_case(terrain,plateau)->terrain->nb_maison-=1;
}

/*ajoute un terrain a un joueur si il est libre*/
void achat_terrain(int terrain, int joueur, PLATEAU *plateau) {
	int i;
	if (ptr_case(terrain,plateau)->terrain->proprietaire != -1) return; /*verifie que le terrain est libre*/
	ptr_case(terrain,plateau)->terrain->proprietaire=joueur;
	plateau->joueurs[joueur]->terrains.nb_terrain++;
	i=0;
	while (plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i] != NULL)
		i++;
	plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i]=ptr_case(terrain,plateau)->terrain;
	if (ptr_case(terrain,plateau)->terrain->couleur == GARES) {
		i=0;
		while (i < 4 && plateau->joueurs[joueur]->terrains.T[GARES][i] != NULL)
			i++;
		if (i == 4)
			plateau->joueurs[joueur]->terrains.terr_complet[GARES]=1;
		return;
	}
	if (ptr_case(terrain,plateau)->terrain->couleur > MARRON && ptr_case(terrain,plateau)->terrain->couleur < BLEU) {
		i=0;
		while (i < 3 && plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i] != NULL)
			i++;
		if (i == 3)
			plateau->joueurs[joueur]->terrains.terr_complet[ptr_case(terrain,plateau)->terrain->couleur]=1;
		return;
	}
	i=0;
	while (i < 2 && plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i] != NULL)
		i++;
	if (i == 2)
		plateau->joueurs[joueur]->terrains.terr_complet[ptr_case(terrain,plateau)->terrain->couleur]=1;
}

/*libere le terrain d'un joueur si il est occupe mais sans maison*/
void vente_terrain(int terrain, int joueur, PLATEAU *plateau) { 
	int i;
	if (ptr_case(terrain,plateau)->terrain->proprietaire == -1 || ptr_case(terrain,plateau)->terrain->nb_maison > 0)
		return; /*vente si non libre, si pas de maison*/
	ptr_case(terrain,plateau)->terrain->proprietaire=-1;
	plateau->joueurs[joueur]->terrains.nb_terrain--;
	i=0;
	while (ptr_case(terrain,plateau)->terrain != plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i] && i<4){
		i++;
	}
	plateau->joueurs[joueur]->terrains.T[ptr_case(terrain,plateau)->terrain->couleur][i]=NULL;
	plateau->joueurs[joueur]->terrains.terr_complet[ptr_case(terrain,plateau)->terrain->couleur]=0;
}

/*inverse l'etat d'obtention de la carte sortie de prison*/
/*1 si 0 ; 0 si 1*/
void modif_sortie_de_prison(int joueur, PLATEAU *plateau) { /*passe à 1 si 0 ; passe à 0 si 1*/
	plateau->joueurs[joueur]->carte_spe.sortie_prison=(plateau->joueurs[joueur]->carte_spe.sortie_prison+1)%2;
}

/*hypotheque ou deshypotheque un terrain (si possible)*/
/*passe à -1 si 0 ; passe a 0 si -1 ; ne fait rien si >= 1*/
void modif_hypotheque(int terrain, PLATEAU *plateau) { /*passe à -1 si 0 ; passe a 0 si -1 ; ne fait rien si >= 1*/
	if (ptr_case(terrain,plateau)->terrain->nb_maison > 0) return;
	ptr_case(terrain,plateau)->terrain->nb_maison=((ptr_case(terrain,plateau)->terrain->nb_maison+2)%2)-1;
}

/*deplace le joueur vers nouvelle_case*/
void deplacement_joueur (int joueur, int nouvelle_case, PLATEAU *plateau) {
	ptr_case(plateau->joueurs[joueur]->position,plateau)->joueur[joueur]=0;
	plateau->joueurs[joueur]->position=nouvelle_case;
	ptr_case(nouvelle_case,plateau)->joueur[joueur]=1;
}

/*retire un joueur du jeu*/
void virer_joueur(int joueur, PLATEAU *plateau) {
	plateau->present[joueur]=0;
}

/*place ou retire un joueur de prison*/
void etat_prison(int joueur, PLATEAU *plateau) { /*0 si 1 ; 1 si 0*/
	plateau->prison[joueur]=(plateau->prison[joueur]+1)%2;
}



/*________________________________________________________________________________________________*/

/*donne le pointeur de la n-ième case (n de 1 à 40)*/
CASE *ptr_case(int n, PLATEAU *plateau) {
	CASE *ptr=plateau->case_depart;
	int i;
	for (i=1; i<n; i++) {
		ptr=ptr->suivante;
	}
	return ptr;
}

/*copie un chaine de caracteres dans une autre*/
void copie_string(char *src, char *dest) {
	int i=0;
	while (src[i] != '\0') {
		dest[i]=src[i];
		i++;
	}
}

 /*concatene 2 mot*/
void cat(char *mot1, char *mot2){
	int i=0,j=0;
	while (mot1[i]!='\0') {
		/*printf("\n");
		printf("%c",mot1[i]);*/
		i++;
	}
	while (mot2[j]!='\0') {
		mot1[i]=mot2[j];
		i++;
		j++;
	}
	mot1[i]='\0';
}



