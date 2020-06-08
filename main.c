#include <stdio.h>
#include <stdlib.h>


#include "lib/interface_graphique.h"

int main() {

	PLATEAU *plateau;
	int quitter=0;
	int ecran_demarrage=1;
	int joueur_courant;
	int etape=0; /****	etape 0 : debut du jeu -> les joueurs achetent les terrains sur lesquels ils tombent
	 	 	 	 		etape 1 : tout les terrains sont achetés -> les joueurs peuvent vendre leur terrains et placer des maisons
	 	 	 	 ****/
	int bouton;
	int *parc_gratuit;
	parc_gratuit=(int *)malloc(sizeof(int));
	*parc_gratuit=0;
	int rejoue;

	int des_double[4], i; /***pour compter les doubles de chaque joueur***/
	for (i=0; i<4; i++)
		des_double[i]=0;

	int wait_prison[4]; /***pour compter le nombre de tours en prison de chaque joueur***/
	for (i=0; i<4; i++)
		wait_prison[i]=0;
	
	int *a,*b; /* variables pour les dés */
	a=(int *)malloc(sizeof(int));
	b=(int *)malloc(sizeof(int));
	
	int *nouvel_effet;
	nouvel_effet=(int *)malloc(sizeof(int));
	
	File *F;
	F=(File *)malloc(sizeof(File));
    init_file(F); 
	
	int choix;
	int joueur;
	int terrain;
	int prix;
	int validation; /*1 si accepté; 0 sinon*/
	int cpt;
	int choix_pris;
	int som;
	int saute_un_tour;
	int pos;
	int joueur_qui_gagne_des_sous;
	int oui;
	int s;
	int l;

	/* boucle de jeu */
	while (quitter == 0) {

		if (ecran_demarrage == 1) { /* en début de partie */
			/* affichage ecran demarrage, (1) si nouvelle partie, (2) si charger sauvegarde, (3) quitter */
			choix= affiche_ecran_demarrage();

			if(choix==1) {/***Evenement nouvelle partie***/
				/* récupération nom des joueurs */
				quitter=recuperation_stokage_noms();
				if(quitter==-1) continue;
				/* lancer dés pour ordre */
				plateau=init_plateau();
				char nom[4][15];
				char n[15];
				nom_joueur(n,0,plateau);
				strcpy(nom[0],n);
				nom_joueur(n,1,plateau);
				strcpy(nom[1],n);
				nom_joueur(n,2,plateau);
				strcpy(nom[2],n);
				nom_joueur(n,3,plateau);
				strcpy(nom[3],n);
				quitter=affiche_lancer_de(nom);
				if (quitter==4) continue;
				joueur_courant=0;
				plateau=init_plateau(); /***Chargement d'un nouveau plateau***/
				ecran_demarrage=0;

			} else if (choix== 2){ /***Evenement partie sauvegarde***/
				plateau=charger_sauvegarde(); /***Chargement de la sauvegarde***/
				joueur_courant=joueur_courant_sauv(); /***Chargement du joueur courant***/
				*parc_gratuit=parc_gratuit_sauv(); /*chargement parc gratuit*/
				F->tete=tete_file_sauv(); /*chargement tete de file*/
				ecran_demarrage=0;
			} else if (choix==0 || choix==3){ /***Quitter***/
				quitter=1;

			}
		}

		if (ecran_demarrage == 0) { /* en cours de partie */

			rejoue=0;
			/* affichage plateau jeu */
			quitter=affiche_plateau(joueur_courant,plateau,parc_gratuit,0,a,b,F->tete);
			if (quitter==-1) continue; /* sauvegarder et quitter */
			else if (quitter==-2) {
				/* demande a l'utilisateur si il veut quitter sans sauvegarder */
				quitter=quitter_sauve();
				if (quitter==1) continue; /* oui */
				else quitter=0; /* non */
			}

			/*** test fin etape 0 ***/
			if(tout_achete(plateau)==1) etape=1;
			
			if (etape == 1) { /* si tous les terrains ont ete achetes */
				bouton=0;
				while (bouton >= 0 && bouton <=3) {
					/* Affichage boutons
					 * While pas appuyé (0) OU bouton achat_terrain (1) OU bouton achat_maison (2) OU bouton lancer de dé (3)
					 * -> bouton prend une valeur*/
					bouton=debut_tour();
					switch (bouton) {
						case 1:
							/*
							 * affichage
							achat d'un terrain a qqn -> proposition
							-> mettre a jour les variables
							*/
							proposition_achat_terrain(plateau,joueur_courant,&joueur,&terrain,&prix,&validation);
							if (validation == 1) {
								vente_terrain(terrain,joueur,plateau);
								achat_terrain(terrain,joueur_courant,plateau);
								modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)-prix,plateau);
								modif_compte_joueur(joueur,compte_joueur(joueur,plateau)+prix,plateau);
							}
							bouton=0;
							break;
						case 2:
							/*
							 * affichage
							construction d'une maison sur un terrain
								-> renvoie un terrain
							*/
							if(achat_maison(plateau,joueur_courant,&terrain)==1){
								ajout_maison(terrain,plateau);
								modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)-prix_construction(terrain,plateau),plateau);
							}
							bouton=0;
							break;
						case 3:
							bouton=5; /***Sortir de la boucle***/
							break;
					}
				}
			}

			if (prisonnier(joueur_courant,plateau) == 1) { /* si prisonnier */
				/*
				gerer la prison  (sortie au bout de trois tours)
				*/
				wait_prison[joueur_courant]++;
				if (wait_prison[joueur_courant] >= 3) {
					/***payer 50 et sortir***/
                    cpt = compte_joueur(joueur_courant, plateau);
                    modif_compte_joueur(joueur_courant, cpt-50, plateau);
					etat_prison(joueur_courant,plateau);
				}
				else {
					/* choix (payer, carte, double) (0) (1) (2)*/
					do {
						choix_pris=choix_prison();
					} while (choix_pris==1 && sortie_de_prison(joueur_courant,plateau)==0) ;
					/* //!\\ verifier si (1) est dispo*/
					switch (choix_pris) {
					case 0:
						/***payer***/
                        cpt = compte_joueur(joueur_courant, plateau);
                        modif_compte_joueur(joueur_courant, cpt-50, plateau);
						wait_prison[joueur_courant]=0;
						etat_prison(joueur_courant,plateau);
						break;
					case 1:
						/* utiliser carte sortie prison */
						modif_sortie_de_prison(joueur_courant,plateau);
						etat_prison(joueur_courant,plateau);
						break;
					case 2:
						/***tirage aux dés***/
						/***ne rien ajouter***/
						break;
					}
				}
			}

			/****lancer de des****/
			saute_un_tour=0;
			
            /*lancer dés graphiquement et affichage plateau*/
            quitter=affiche_plateau(joueur_courant,plateau,parc_gratuit,1,a,b,F->tete);
			if (quitter==-1 || quitter==-2) {
				/* on ne peut pas quitter en milieu de tour */
				erreur(1);
				quitter=0;
			}

            som = *a + *b;
            if(*a == *b) { /* si double */
            	if (prisonnier(joueur_courant,plateau) == 0) {
					/* si on est pas prisonnier on rejoue au prochan tour */
					des_double[joueur_courant]++;
					rejoue=1;
                } else {
					/* sinon on sort de prison */
					etat_prison(joueur_courant,plateau);
				}
            } else if(prisonnier(joueur_courant,plateau) == 1) {
				/* si on fait pas de double et qu'on est en prison on passe son tour */
                saute_un_tour=1;
			}

			if (saute_un_tour == 0) { /* si on passe pas son tour */

				/****trop de double****/
				if (wait_prison[joueur_courant] != 0 && des_double[joueur_courant] == 3) {
					/* si on a fait trop de double on va en prison */
					allez_en_prison(joueur_courant,plateau);
					des_double[joueur_courant]=0;
					rejoue=0;
				}

				/****deplacement du joueur****/
				pos=position_joueur(joueur_courant,plateau);
				pos+=som;
				if (pos>40) {
					pos=pos-40;
					if (pos>1) modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)+200,plateau);
				}
				deplacement_joueur(joueur_courant,pos,plateau);
				
				/*afficher position du joueur*/
				quitter=affiche_plateau(joueur_courant,plateau,parc_gratuit,0,a,b,F->tete);
				if (quitter==-1 || quitter==-2){
					/* on ne peut pas quitter en milieu de tour */
					erreur(1);
					quitter=0;
				}
				
				/****effet de la case****/
				do {
					*nouvel_effet=0;
					pos=position_joueur(joueur_courant,plateau);
					if (pos == 1 || pos == 3 || pos == 5 || pos == 8 || pos == 18 || pos == 21 || pos == 23 || pos == 31 || pos == 34 || pos == 37 || pos == 39) {
						switch (pos) {
						case 1:
							case_depart(joueur_courant,plateau); /* si on est sur la case depart */
							break;
						case 5:
							impots_sur_revenu(joueur_courant,parc_gratuit,plateau); /* si on est sur la case frais de douane */
							info_payer(plateau,joueur_courant ,pos);
							break;
						case 21:
							case_parc_gratuit(joueur_courant,parc_gratuit,plateau); /* si on est sur la case open source */
							break;
						case 31:
							allez_en_prison(joueur_courant,plateau); /* si on est sur la case segmentation fault */
							rejoue=0;
							break;
						case 39:
							taxes(joueur_courant,parc_gratuit,plateau); /* si on est sur la case depot de brevet */
							info_payer(plateau,joueur_courant ,pos);
							break;
						default:
							/***cartes chances***/
							chance(joueur_courant,parc_gratuit,nouvel_effet,plateau,F);
						}
					} else if (pos==11) {
						/* visite prison, rien a faire */	
					} else {
						/***terrain***/
						if (proprietaire_terrain(pos,plateau) == -1) { /* si terrain libre */
							/* affichage
							 * choix si achat*/
							oui=choix_achat_terrain(plateau,pos,joueur_courant);
							if (oui == 1) {
								/* achat du terrain */
								achat_terrain(pos,joueur_courant,plateau);
								modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)-prix_terrain(pos,plateau),plateau);
							}
						} else if(proprietaire_terrain(pos,plateau) != joueur_courant){
							/* si le terrain n'est pas libre et qu'il nous appartient pas -> payer loyer */
							info_payer(plateau,joueur_courant ,pos);
							l=loyer(joueur_courant,pos,plateau);
							joueur_qui_gagne_des_sous=proprietaire_terrain(pos,plateau);
							modif_compte_joueur(joueur_qui_gagne_des_sous,compte_joueur(joueur_qui_gagne_des_sous,plateau)+l,plateau);
							modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)-l,plateau);
						} else {
							/* si le terrain nous appartient */
							/* regarde si le terrain est hypothéqué et propose de le racheter*/
							if (test_hypotheque(pos,plateau)){
								/* affichage rachat hypotheque */
								oui=rachat_hypotheque(plateau,pos,joueur_courant);
								if (oui==1){
									modif_hypotheque(pos,plateau);
									modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)-valeur_hypothequaire(pos,plateau),plateau);
								}
							}
						}
					}
				} while (*nouvel_effet == 1);

				/****Si ruiné****/
				while (compte_joueur(joueur_courant,plateau) < 0 && a_sec(joueur_courant,plateau) == 0) {
					/*affichage CHOIX vente maison (0) / hypotheque terrain (1) / vente carte prison (2)*/
					choix=si_joueur_ruine();
					switch (choix) {
						case 0:
							/*selection maison et confirmation
								-> renvoie le terrain concerné*/
							terrain=choix_proprietes_maison(plateau,joueur_courant);
							if (terrain>0) {
								choix=choix_maisons(plateau,joueur_courant,terrain);
								if (choix==-1) {
									/* rien a faire */
								} else if(choix==5){ /* vente hotel */
									vente_maison(terrain,plateau);
									modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)+prix_construction(terrain,plateau),plateau);
								} else { /* vente maisons */
									for (i=0;i<choix;i++){
										vente_maison(terrain,plateau);
										modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)+prix_construction(terrain,plateau),plateau);	
									}
								}
							}
							break;
						case 1:
							/*selection terrain et confirmation
								-> renvoie le terrain concerné*/
							terrain=choix_proprietes_hypotheque(plateau,joueur_courant);
							if (terrain!=-1) { /* hypotheque terrain */
								modif_hypotheque(terrain,plateau);
								modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)+valeur_hypothequaire(terrain,plateau),plateau);
							}
							break;
						case 2:
							/* selection vente carte sortie prison */
							if (sortie_de_prison(joueur_courant,plateau) == 0) {
								/* le joueur ne la possede pas */
								pas_de_carte();
							} else {
								/*confirmer la vente de la carte*/
								oui=vendre_carte();
								if (oui == 1) {
									modif_sortie_de_prison(joueur_courant,plateau);
									modif_compte_joueur(joueur_courant,compte_joueur(joueur_courant,plateau)+25,plateau);
								}
							}
						default:
							break;
					}
				}

				/****joueur mis hors jeu****/
				if (compte_joueur(joueur_courant,plateau) < 0) {
					/* affichage perdant */
					perdu(plateau,joueur_courant);
					virer_joueur(joueur_courant,plateau);
					rejoue=0;
					/***transfert des terrains hypothequés a la banque***/
					transfert_terrains_banque(joueur_courant,plateau);
				}	

			} /*fin du saut de tour*/

			/****joueur suivant****/
			if (rejoue == 0) {
				do {
					joueur_courant++; /***boucle et prend en compte les joueurs absents***/
					if (joueur_courant == 4){
						joueur_courant=0;
					}
				} while (joueur_present(joueur_courant,plateau) == 0);
			}

			/****test si gagnant****/
			s=0;
			for (i=0; i<4; i++)
				s=s+joueur_present(i,plateau); /* compte le nombre de joueurs encore presents */
			if (s == 1) {
				/*affichage pour le gagnant (le gagnant est forcement joueur_courant)*/
				victoire(plateau,joueur_courant);
				ecran_demarrage=1; /***Retour ecran de demarrage***/
			}

		}

	}
	free_plateau(plateau);
	free(a);
	free(b);
	free(F);
	free(parc_gratuit);
	free(plateau);
	free(nouvel_effet);
	return 1;
}
