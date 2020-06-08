#include <stdio.h>
#include <stdlib.h>


#include "init.h"

/*permet de construire la structure du plateau en mémoire et de l'initialiser*/
PLATEAU *init_plateau() {
	PLATEAU *plateau;
	CASE *case_plateau, *case_suiv;
	JOUEUR *joueur;
	TERRAIN *terrain;
	int tab[9];
	int i, j, k;

	/*definition du plateau -> definition des joueurs*/
	plateau=(PLATEAU *) malloc(sizeof(PLATEAU));
	plateau->taille=40;
	for (i=0; i<4; i++){
		plateau->present[i]=1;
		plateau->prison[i]=0;
	}
	for (i=0; i<4; i++) { /*definition des joueurs*/
		joueur=(JOUEUR *) malloc(sizeof(JOUEUR));
		lire_joueur(joueur->nom,i+1);
		joueur->position=1;
		joueur->compte=1500;
		joueur->carte_spe.sortie_prison=0;
		/*autre?*/
		joueur->terrains.nb_terrain=0;
		for (j=0; j<10; j++)
			joueur->terrains.terr_complet[j]=0;
		for (j=0; j<10; j++)
			for (k=0; k<4; k++)
				joueur->terrains.T[j][k]=NULL;
		plateau->joueurs[i]=joueur;
	}

	/*definition de la case depart (liee au plateau)*/
	case_plateau=(CASE *) malloc(sizeof(CASE));
	plateau->case_depart=case_plateau;
	lire_nom(case_plateau->nom,1);
	for (i=0; i<4; i++)
		case_plateau->joueur[i]=1;
	case_plateau->terrain=NULL;

	/*definition des autres cases (liees à la case depart) -> definition des terrains*/
	for (i=1; i<40; i++) {
		case_suiv=(CASE *) malloc(sizeof(CASE));
		case_plateau->suivante=case_suiv;
		lire_nom(case_suiv->nom,i+1);
		for (j=0; j<4; j++)
			case_suiv->joueur[j]=0;
		case_suiv->precedente=case_plateau;

		if (lire_type_terrain(i+1) == AUCUN)
			case_suiv->terrain=NULL;
		else { /*definition des terrains (lies aux cases du plateau)*/
			terrain=(TERRAIN *) malloc(sizeof(TERRAIN));
			lire_nom(terrain->nom,i+1);
			terrain->couleur=lire_type_terrain(i+1);
			lire_terrain(tab,i+1);
			terrain->prix=tab[0];
			terrain->prix_batiment=tab[1];
			terrain->hypotheque=tab[2];
			terrain->loyer.nu=tab[3];
			terrain->loyer.m1=tab[4];
			terrain->loyer.m2=tab[5];
			terrain->loyer.m3=tab[6];
			terrain->loyer.m4=tab[7];
			terrain->loyer.H=tab[8];
			terrain->proprietaire=-1;
			terrain->nb_maison=0;

			case_suiv->terrain=terrain;
		}

		case_plateau=case_suiv;
	}
	plateau->case_depart->precedente=case_plateau; /*bouclage du plateau*/
	plateau->case_depart->precedente->suivante=plateau->case_depart; /*bouclage du plateau*/

	return plateau;
}

/*permet de construire la structure du plateau en mémoire et de l'initialiser a partir de la sauvegarde*/
PLATEAU *charger_sauvegarde() {
	FILE *f;
	PLATEAU *plateau;
	CASE *case_plateau, *case_suiv;
	JOUEUR *joueur;
	TERRAIN *terrain;
	int i;
	int joueur_cour,parc_gratuit,tete;

	/*ouverture de la sauvegarde*/
	f=fopen("src/sauv.bin","rb");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return NULL;
	}

	fread(&joueur_cour,sizeof(int),1,f);
	fread(&parc_gratuit,sizeof(int),1,f);
	fread(&tete,sizeof(int),1,f);

	/*definition du plateau -> definition des joueurs*/
	plateau=(PLATEAU *) malloc(sizeof(PLATEAU));
	fread(plateau,sizeof(PLATEAU),1,f);
	for (i=0; i<4; i++) { /*definition des joueurs*/
		joueur=(JOUEUR *) malloc(sizeof(JOUEUR));
		fread(joueur,sizeof(JOUEUR),1,f);
		plateau->joueurs[i]=joueur;
	}

	/*definition des cases -> definition des terrains*/
	case_plateau=(CASE *) malloc(sizeof(CASE));
	fread(case_plateau,sizeof(CASE),1,f);
	plateau->case_depart=case_plateau;

	for (i=1; i<40; i++) {
		case_suiv=(CASE *) malloc(sizeof(CASE));
		fread(case_suiv,sizeof(CASE),1,f);
		case_plateau->suivante=case_suiv;
		case_suiv->precedente=case_plateau;

		if (case_suiv->terrain != NULL) {/*definition des terrains (lies aux cases du plateau)*/
			terrain=(TERRAIN *) malloc(sizeof(TERRAIN));
			fread(terrain,sizeof(TERRAIN),1,f);
			case_suiv->terrain=terrain;
		}

		case_plateau=case_suiv;
		case_suiv=case_suiv->suivante;
	}
	plateau->case_depart->precedente=case_plateau; /*bouclage du plateau*/
	plateau->case_depart->precedente->suivante=plateau->case_depart; /*bouclage du plateau*/

	fclose(f);
	return plateau;
}

/*lire le joueur courant d'apres la sauvegarde (entre 0 et 3)*/
int joueur_courant_sauv() {
	FILE *f;
	int joueur_cour;
	f=fopen("src/sauv.bin","rb");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return 0;
	}
	fread(&joueur_cour,sizeof(int),1,f);
	fclose(f);
	return joueur_cour;
}

/*lire la valeur du parc gratuit d'apres la sauvegarde */
int parc_gratuit_sauv(){
	FILE *f;
	int joueur_cour,parc_gratuit;
	f=fopen("src/sauv.bin","rb");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return 0;
	}
	fread(&joueur_cour,sizeof(int),1,f);
	fread(&parc_gratuit,sizeof(int),1,f);
	fclose(f);
	return parc_gratuit;	
}

/*lire la valeur de la tete de la file d'apres la sauvegarde */
int tete_file_sauv(){
	FILE *f;
	int joueur_cour,parc_gratuit,tete;
	f=fopen("src/sauv.bin","rb");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return 0;
	}
	fread(&joueur_cour,sizeof(int),1,f);
	fread(&parc_gratuit,sizeof(int),1,f);
	fread(&tete,sizeof(int),1,f);
	fclose(f);
	return tete;
}

/*permet de sauvegarder le plateau*/
void sauvegarder(int joueur_courant, PLATEAU *plateau, int parc_gratuit, int tete) {
	FILE *f;
	int i;
	CASE *ptr;
	f=fopen("src/sauv.bin","wb");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	fwrite(&joueur_courant,sizeof(int),1,f);
	fwrite(&parc_gratuit,sizeof(int),1,f);
	fwrite(&tete,sizeof(int),1,f);
	fwrite(plateau,sizeof(PLATEAU),1,f);
	for (i=0; i<4; i++)
		fwrite(plateau->joueurs[i],sizeof(JOUEUR),1,f);
	ptr=plateau->case_depart;
	for (i=0; i<40; i++) {
		fwrite(ptr,sizeof(CASE),1,f);
		if (ptr->terrain != NULL)
			fwrite(ptr->terrain,sizeof(TERRAIN),1,f);
		ptr=ptr->suivante;
	}
	fclose(f);
}

/* permet de lire les infos d'un joueur dans le fichier */
void lire_joueur(char *dest, int n) {
	FILE *f;
	int x;
	char ligne[50];
	f=fopen("src/init.txt","r");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	while (fgets(ligne,sizeof(ligne),f)[0] != '1') {}
	x=0;
	while (x != n)
		fscanf(f,"\t%d:%s",&x,dest);
	fclose(f);
}

/* permet de lire le nom d'un joueur dans le fichier */
void lire_nom(char *dest, int n) {
	FILE *f;
	int x;
	char ligne[50];
	f=fopen("src/init.txt","r");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	while (fgets(ligne,sizeof(ligne),f)[0] != '2') {}
	x=0;
	while (x != n)
		fscanf(f,"\t%d:%s",&x,dest);
	fclose(f);
}

/* lit la couleur du terrain dans le fichier */
COULEUR lire_type_terrain(int n) { /*AUCUN si rien à lire*/
	FILE *f;
	int x;
	char ch[20];
	int couleur;
	char ligne[50];
	f=fopen("src/init.txt","r");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return AUCUN;
	}
	while (fgets(ligne,sizeof(ligne),f)[0] != '3') {}
	x=0;
	while (x != n)
		fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&couleur);
	fclose(f);
	return (COULEUR) couleur;
}

/* permet de lire les infos d'un terrain dans le fichier */
void lire_terrain(int *tab, int n) { /*NULL si rien à lire*/
	FILE *f;
	char ch[20];
	int x, i;
	char ligne[50];
	f=fopen("src/init.txt","r");
	if (f == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	while (fgets(ligne,sizeof(ligne),f)[0] != '3') {}
	x=0;
	while (x != n)
		fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&i);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[0]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[1]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[2]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[3]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[4]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[5]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[6]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[7]);
	fscanf(f,"\t%d:\t%s :%d\n",&x,ch,&tab[8]);
	fclose(f);
}

/* permet de liberer l'epace memoire du plateau */
void free_plateau(PLATEAU *plateau) {
	CASE *ptr=plateau->case_depart;
	CASE *ptr2;
	int i;
	for (i=0; i<4; i++)
		free(plateau->joueurs[i]);
	for (i=0; i<40; i++) {
		if (ptr->terrain != NULL)
			free(ptr->terrain);
		ptr2=ptr->suivante;
		free(ptr);
		ptr=ptr2;
	}
}

/*changer le nom d'un joueur dans le fichier init.txt*/
void changer_nom_joueur(int joueur, char *nom) {
	FILE *fr, *fw;
	int x;
	char ch[20];
	char ligne[50];
	fr=fopen("src/init.txt","r");
	if (fr == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	fw=fopen("src/temp.txt","w");
	if (fw == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	while (feof(fr) == 0) {
		fgets(ligne,sizeof(ligne),fr);
		fputs(ligne,fw);
	}
	fclose(fr);
	fclose(fw);
	fr=fopen("src/temp.txt","r");
	if (fr == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	fw=fopen("src/init.txt","w");
	if (fw == NULL) {
		printf("erreur d'ouverture du fichier");
		return;
	}
	while (fgets(ligne,sizeof(ligne),fr)[0] != '1')
		fputs(ligne,fw);
	fputs(ligne,fw);
	x=0;
	while (x != joueur) {
		fscanf(fr,"\t%d:%s\n",&x,ch);
		fprintf(fw,"\t%d:%s\n",x,ch);
	}
	fscanf(fr,"\t%d:%s\n",&x,ch);
	fprintf(fw,"\t%d:%s\n",joueur+1,nom);
	if (joueur != 3) fputc('\t',fw);
	while (feof(fr) == 0) {
		fgets(ligne,sizeof(ligne),fr);
		fputs(ligne,fw);
	}
	fclose(fr);
	fclose(fw);
	remove("src/temp.txt");
}

