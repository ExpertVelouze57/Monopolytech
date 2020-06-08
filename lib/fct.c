#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "fct_elem.h"
#include "fct.h"
#include "interface_graphique.h"


/*Fonction qui ajoute la valeur du parc gratuit sur le compte du joueur, puis remet parc gratuit à 0*/
void case_parc_gratuit(int joueur, int *parc_gratuit, PLATEAU *plateau) {
	modif_compte_joueur(joueur,compte_joueur(joueur,plateau)+(*parc_gratuit),plateau);
	*parc_gratuit=0;
}

/*Fonction utilisée lorsqu'un joueur s'arrête sur la case départ, il recoit 400pp*/
void case_depart(int joueur, PLATEAU *plateau) {
	modif_compte_joueur(joueur,compte_joueur(joueur,plateau)+400,plateau);
}

/*enlève 100 au joueur courant, +100 parc gratuit*/
void taxes(int joueur, int *parc_gratuit, PLATEAU *plateau) {
	modif_compte_joueur(joueur,compte_joueur(joueur,plateau)-100,plateau);
	*parc_gratuit+=100;
}

/*enlève 200 au joueur courant, +200 parc gratuit*/
void impots_sur_revenu(int joueur, int *parc_gratuit, PLATEAU *plateau) {
	modif_compte_joueur(joueur,compte_joueur(joueur,plateau)-200,plateau);
	*parc_gratuit+=200;
}

/*fct qui envoie le joueur en prison, et donc modifie la variable associé*/
void allez_en_prison(int joueur, PLATEAU *plateau) {
	deplacement_joueur(joueur,11,plateau);
	etat_prison(joueur,plateau);
}

/*renvoie 0 si le joueur peut encore gagner de l'argent en vendant quelque chose, ou 1 sinon*/
int a_sec(int joueur, PLATEAU *plateau) {
	int i,cpt=0;
	if (sortie_de_prison(joueur,plateau) == 1) return 0;
	
	CASE *c;
	i=2;
	for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
		if (c->terrain!=NULL) {
			if (proprietaire_terrain(i,plateau)==joueur	&& test_hypotheque(i,plateau)==0) {
				cpt++;	
			}
		}
		i++;
	}
	if (cpt>0) return 0;
	return 1;
}

/*transfert tout les terrains du joueur qui ne peut pas payer au joueur à qui il doit de l'argent*/
void transfert_terrains(int joueur, int joueur_qui_gagne, PLATEAU *plateau) {
	int i, j;
	TERRAIN *terrain;
	for (i=0; i<10; i++) {
		for (j=0; j<4; j++) {
			terrain=plateau->joueurs[joueur]->terrains.T[i][j];
			if (terrain != NULL) {
				int k=1;
				CASE *c=plateau->case_depart;
				while (c->terrain != terrain) {
					c=c->suivante;
					k++;
				}
				vente_terrain(k,joueur,plateau);
				achat_terrain(k,joueur_qui_gagne,plateau);
			}
		}
	}
}

/*transfert tout les terrains du joueur qui ne peut pas payer à la banque lorsqu'il doit de l'argent à la banque (case impôts par exemple)*/
void transfert_terrains_banque(int joueur, PLATEAU *plateau) {
	int i;
	CASE *c;
	i=2;
	for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
		if (c->terrain!=NULL){
			if (proprietaire_terrain(i,plateau)==joueur){
				modif_hypotheque(i,plateau);
				vente_terrain(i,joueur,plateau);	
			}
		}
		i++;
	}
}

/*fct qui réportorie tout les effets des cases chances et effectue les modification nécessaires*/
void chance(int joueur, int *parc_gratuit, int *nouvel_effet, PLATEAU *plateau, File *F){
    int cpt,numero;
    
    /*afficher_file(F);*/
    numero = defile(F);
    
    switch (numero){
        case 0 :
			action_carte(1,0,"");
            cpt = position_joueur(joueur, plateau);
            if(cpt == 3)
                deplacement_joueur (joueur, cpt+37,  plateau);
            else
                deplacement_joueur (joueur, cpt-3, plateau);
            *nouvel_effet = 1;
            break;
            
        case 1 :
			action_carte(2,100,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+100, plateau) ;
            break;
        
        case 2 :
			action_carte(3,50,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-50, plateau);
            *parc_gratuit +=50;
            break;
            
        case 3 :
            /*prison*/
			action_carte(4,0,"");
            allez_en_prison(joueur, plateau);
            break;
        
        case 4 :
			action_carte(2,20,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+20, plateau);
            break;
            
        case 5 :
			action_carte(2,50,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+50, plateau);
            break;
            
        case 6 :
			action_carte(3,100,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-100, plateau);
            *parc_gratuit +=100;
            break;
        
        case 7 :
			action_carte(5,0,"MacOS");
            /*aller à la deuxième gare = MacOS*/
            if((position_joueur(joueur, plateau)) < 16){ /*passe PAS par départ */
				deplacement_joueur (joueur, 16, plateau);
            }
            else{
                /*passe par départ donc +200*/
                deplacement_joueur (joueur, 16, plateau);
                cpt = compte_joueur(joueur, plateau);
            	modif_compte_joueur(joueur, cpt+200, plateau) ;
            }
			*nouvel_effet=1;
            break;
         
        case 8 :
			action_carte(2,10,"");
            cpt =compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+10, plateau);
            break;
            
        case 9 :
			action_carte(7,0,"");
            /*reparation des maisons 40 et hotels 115*/
            if(nb_terrains_joueur(joueur,plateau)==0)
                break;
            else{
                int somme=0;
				CASE *c;
				for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
					if (c->terrain!=NULL){
						if (c->terrain->proprietaire==joueur){
							if (c->terrain->nb_maison==5) somme+=115;
							else if (c->terrain->nb_maison>0) somme+=40*c->terrain->nb_maison;
							else somme+=0;
						}
					}
				}
				cpt = compte_joueur(joueur, plateau);
				modif_compte_joueur(joueur, cpt-somme, plateau);                        
            }
            break; 
            
        
        case 10 :
			action_carte(2,200,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+200, plateau);
            break;
            
        case 11 : 
			action_carte(3,150,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-150, plateau);
            *parc_gratuit += 150;
            break;
            
        case 12 :
			action_carte(3,15,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-15, plateau);
            *parc_gratuit +=15;
            break;
            
        case 13 :
			action_carte(6,0,"Php");
            deplacement_joueur (joueur, 2, plateau);
            break;
            
        case 14 : 
			action_carte(2,150,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+150, plateau);
            break;
            
        case 15 :
            /*case départ*/
			action_carte(5,0,"Main()");
            deplacement_joueur (joueur, 1, plateau);
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+400, plateau);
            break;
            
        case 16 :
			action_carte(3,20,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-20, plateau);
            *parc_gratuit+=20;
            break;
            
        case 17 :
			action_carte(3,50,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt-50, plateau);
            *parc_gratuit+=50;
            break;
            
        case 18 :
			action_carte(8,0,"");
            /*reparation des maisons 25 et hotels 100*/
            if(nb_terrains_joueur(joueur,plateau)==0)
                break;
            else{
                int somme=0;
                                
                CASE *c;
				for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
					if (c->terrain!=NULL){
						if (c->terrain->proprietaire==joueur){
							if (c->terrain->nb_maison==5) somme+=100;
							else if (c->terrain->nb_maison>0) somme+=25*c->terrain->nb_maison;
							else somme+=0;
						}
					}
				}
				cpt = compte_joueur(joueur, plateau);
				modif_compte_joueur(joueur, cpt-somme, plateau);
			}
            break;
        
        case 19 : 
			action_carte(2,25,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+25, plateau);
            break;
                        
        case 20 :
            /*carte sortie de prison*/
			action_carte(9,0,"");
            if(sortie_de_prison(joueur, plateau) == 0)
                modif_sortie_de_prison(joueur, plateau);
            break;
       
        case 21 :
			action_carte(2,50,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+50, plateau);
            break;
            
        case 22 : 
            /*case départ*/
			action_carte(5,0,"Main()");
            deplacement_joueur (joueur, 1, plateau);
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+400, plateau);
            break;
            
        case 23 :
			action_carte(4,0,"");
            allez_en_prison(joueur, plateau);
            break;
            
        case 24 :
			action_carte(5,0,"Fortran");
            /*avancez case 12 Fortran*/
            if((position_joueur(joueur, plateau)) < 12) /*passe PAS par départ */
            	deplacement_joueur (joueur, 12, plateau); 
            else{
                /*passe par départ donc +200*/
                deplacement_joueur (joueur, 12, plateau);
                cpt = compte_joueur(joueur, plateau);
            	modif_compte_joueur(joueur, cpt+200, plateau) ;
            }
			*nouvel_effet=1;
            break;
			
        case 25 :
			action_carte(1,0,"");
            cpt = position_joueur(joueur, plateau);
            if(cpt == 3)
                deplacement_joueur (joueur, cpt+37,  plateau);
            else
                deplacement_joueur (joueur, cpt-3, plateau);
            *nouvel_effet = 1;
            break;
			
		case 26 :
			action_carte(2,50,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+50, plateau);
            break;
            
        case 27 :
            /*avancez case 25:Javascript*/
			action_carte(5,0,"Javascript");
            if((position_joueur(joueur, plateau)) < 25) /*passe PAS par départ */
            	deplacement_joueur (joueur, 25, plateau); 
            else{
                /*passe par départ donc +200*/
                deplacement_joueur (joueur, 25, plateau);
                cpt = compte_joueur(joueur, plateau);
            	modif_compte_joueur(joueur, cpt+200, plateau) ;
            }
			*nouvel_effet=1;
            break;
        
        case 28 :
			action_carte(2,100,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+100, plateau);
            break;
            
        case 29 :
			action_carte(6,0,"STM32");
            deplacement_joueur (joueur, 40, plateau);
            break;
          
        case 30 :
			action_carte(2,100,"");
            cpt = compte_joueur(joueur, plateau);
            modif_compte_joueur(joueur, cpt+100, plateau);
            break;
            
        default :
            break;
    }
    return;
}

void init_file(File *F){
    int i;
    for(i=0;i<max;i++){
        F->T[i]=i;
    }
    F->taille = max;
    F->tete = 0;
    
    return;
}

void afficher_file(File F){
    int i;
    for(i=0;i<max;i++)
        printf("%d\n",F.T[i]);
    return;
}

int defile(File *F){
    int elem_depil;
    
    elem_depil =F->T[F->tete];
    
	F->tete = (F->tete + 1) %max;
    
    return elem_depil;
}

/* renvoie 1 si tous les terrains ont ete achetes, -1 sinon */
int tout_achete(PLATEAU *plateau){
	CASE *c;
	int libre=0;
	for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
		if (c->terrain!=NULL){
			if (c->terrain->proprietaire==-1){
				libre+=1;
			} else if (c->terrain->nb_maison>0){
				return 1;	
			}
		}
	}	
	if (libre!=0) return -1;
	return 1;
}
