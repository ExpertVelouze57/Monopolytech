
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "init_joueur.h"
#include "init.h"

int Majusucle;

/*return -1 si quitter, 0 si validé*/
int recuperation_stokage_noms(){
    char Noms_joueurs[4][TAILLE_NOM_JOUEUR];
    Noms_joueurs[0][0]='\0';
    Noms_joueurs[1][0]='\0';
    Noms_joueurs[2][0]='\0';
    Noms_joueurs[3][0]='\0';
    
    int fin = initialisation_nom_joueurs(Noms_joueurs);
    if (fin == -1)
        return -1;
    else{
        changer_nom_joueur(0,Noms_joueurs[0]);
        changer_nom_joueur(1,Noms_joueurs[1]);
        changer_nom_joueur(2,Noms_joueurs[2]);
        changer_nom_joueur(3,Noms_joueurs[3]);
        
        return 0;   
    }
}

/*fct qui indique si 2 chaine sont les mêmes, 1 si identique*/
int initialisation_nom_joueurs(char Noms_joueurs[][TAILLE_NOM_JOUEUR]){
	/*Variables*/
    int a;
	char c;
    int quit =0;
    
    /*initialisation des deux modules video*/
	int temp1 = SDL_Init(SDL_INIT_VIDEO);
    int temp2 = TTF_Init();
    
    /*gestion des erreur sur l'ouverture des module de la sdl*/
    if(temp1 ==-1 || temp2 ==-1){
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init ou SDL_Init : %s    %s\n", TTF_GetError(),SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    
	/*intitialisation des surface*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *S_J1= NULL, *S_J2= NULL, *S_J3= NULL, *S_J4= NULL;
    SDL_Surface *Nom_J1= NULL, *Nom_J2= NULL, *Nom_J3= NULL, *Nom_J4= NULL;
    SDL_Surface *Title =NULL, *Buton_V=NULL, *Texte_V;
    SDL_Surface *image_d1, *image_d2, *image_d3, *image_d4;
    
    /*initilialisation des position*/
	SDL_Rect P_J1,P_J2,P_J3,P_J4;
	SDL_Rect P_t_J1,P_t_J2,P_t_J3,P_t_J4;
    SDL_Rect P_title, P_buton_V, P_t_v;
    SDL_Rect P_im1,P_im2,P_im3,P_im4;
   
    /*Création des police d'affichage*/
    TTF_Font *police = NULL,*police_tt = NULL;
    police = TTF_OpenFont(POLICE_ad, 24);
    police_tt = TTF_OpenFont(POLICE_lb, 40);
    
    /*Creation de couleur*/
	SDL_Color Noire = {0,0,0};
	SDL_Color Blanc = {255,255,255};
	SDL_Color Rouge = {255,0,0};
    SDL_Color Bordeaux = {175,7,3};
    
    /*Création de la fenetre principale*/
    fenetre = SDL_SetVideoMode(1180, 660, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    SDL_WM_SetCaption("Monopolytech : Création des Pseudonyme", NULL);
	
	/*Creation du titre*/
	Title = TTF_RenderText_Shaded(police_tt,"MONOPOLYTECH", Blanc,Rouge);
    
    /*initialisation position titre*/
    creation_pos(&P_title, fenetre->w/2-Title->w/2,50);
    
    /*Chargement des iamage déco*/
    image_d1 = SDL_LoadBMP(Bonhomme_n);
	image_d2 = SDL_LoadBMP(Bonhomme_i);
	image_d3 = SDL_LoadBMP(des_n);
	image_d4 = SDL_LoadBMP(des_i);
    
    /*supression fond image déco*/
    SDL_SetColorKey(image_d1,SDL_SRCCOLORKEY,SDL_MapRGB(image_d1->format,0,255,0));
    SDL_SetColorKey(image_d2,SDL_SRCCOLORKEY,SDL_MapRGB(image_d2->format,0,255,0));
    SDL_SetColorKey(image_d3,SDL_SRCCOLORKEY,SDL_MapRGB(image_d3->format,0,255,0));
    SDL_SetColorKey(image_d4,SDL_SRCCOLORKEY,SDL_MapRGB(image_d4->format,0,255,0));
    
    /*Initialisation position déco*/
    creation_pos(&P_im1, 0,233);
    creation_pos(&P_im2, 920,233);
    creation_pos(&P_im3, 120,70);
    creation_pos(&P_im4, 909,70);
   
    /*Création du bouton*/
    Buton_V = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(Buton_V,SDL_SRCCOLORKEY,SDL_MapRGB(Buton_V->format,255,255,255));
    
    /*ajout texte bouton*/
    Texte_V = TTF_RenderText_Blended(police,"Valider", Blanc);
    
    /*Initialisation de la position du bouton et du texte*/
    creation_pos(&P_buton_V, fenetre->w-(Buton_V->w+75),fenetre->h-(Buton_V->h+50));
    creation_pos(&P_t_v, P_buton_V.x+Buton_V->w/2-Texte_V->w/2,P_buton_V.y+Buton_V->h/2-Texte_V->h/2);

	/*Chargement des images fond nom joueur */
	S_J1 = SDL_LoadBMP(fond_pseudo);
	S_J2 = SDL_LoadBMP(fond_pseudo);
	S_J3 = SDL_LoadBMP(fond_pseudo);
	S_J4 = SDL_LoadBMP(fond_pseudo);
	
	/*Initialisation des position image*/
	creation_pos(&P_J1, fenetre->w/2-S_J1->w/2,200);
	creation_pos(&P_J2, fenetre->w/2-S_J2->w/2,P_J1.y+66);
	creation_pos(&P_J3, fenetre->w/2-S_J3->w/2,P_J2.y+66);
	creation_pos(&P_J4, fenetre->w/2-S_J4->w/2,P_J3.y+66);
	
    /*Création texte initial*/
	Nom_J1 = TTF_RenderText_Blended(police,"Joueur 1", Noire);
	Nom_J2 = TTF_RenderText_Blended(police,"Joueur 2", Noire);
	Nom_J3 = TTF_RenderText_Blended(police,"Joueur 3", Noire);
	Nom_J4 = TTF_RenderText_Blended(police,"Joueur 4", Noire);
    
	/*Initialisation des position texte*/
	creation_pos(&P_t_J1, P_J1.x+8,P_J1.y+6);
	creation_pos(&P_t_J2, P_J2.x+8,P_J2.y+6);
	creation_pos(&P_t_J3, P_J3.x+8,P_J3.y+6);
	creation_pos(&P_t_J4, P_J4.x+8,P_J4.y+6);

    /*affichage du titre*/
    SDL_BlitSurface(Title, NULL,fenetre, &P_title);
    
    /*affichage bouton*/
    SDL_BlitSurface(Buton_V, NULL,fenetre, &P_buton_V);
    SDL_BlitSurface(Texte_V, NULL,fenetre, &P_t_v);
    
    /*Affichage image déco*/
    SDL_BlitSurface(image_d1, NULL,fenetre, &P_im1);
    SDL_BlitSurface(image_d2, NULL,fenetre, &P_im2);
    SDL_BlitSurface(image_d3, NULL,fenetre, &P_im3);
    SDL_BlitSurface(image_d4, NULL,fenetre, &P_im4);
	
	/*Affichage image*/
    SDL_BlitSurface(S_J1, NULL,fenetre, &P_J1);
	SDL_BlitSurface(S_J2, NULL,fenetre, &P_J2);
	SDL_BlitSurface(S_J3, NULL,fenetre, &P_J3);
	SDL_BlitSurface(S_J4, NULL,fenetre, &P_J4);
    
	/*affichage texte*/
	SDL_BlitSurface(Nom_J1, NULL,fenetre, &P_t_J1);
	SDL_BlitSurface(Nom_J2, NULL,fenetre, &P_t_J2);
	SDL_BlitSurface(Nom_J3, NULL,fenetre, &P_t_J3);
	SDL_BlitSurface(Nom_J4, NULL,fenetre, &P_t_J4);
    
	/*actualisation*/
	SDL_Flip(fenetre);
    
    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;    
    
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                /*detection mouvement de souris*/
                case SDL_MOUSEMOTION:
                    /*Bouton validé, modification si souris dessus*/
                    if(event.motion.x > P_buton_V.x && event.motion.x < (P_buton_V.x + 150) && event.motion.y > P_buton_V.y && event.motion.y < (P_buton_V.y + 50)){
                        Texte_V = TTF_RenderText_Blended(police,"Valider", Bordeaux);
                    }
                    else{
                        Texte_V = TTF_RenderText_Blended(police,"Valider", Blanc);
                    }
                    break;
                /*evement si appuye sur le bouton souris*/
				case SDL_MOUSEBUTTONDOWN:
					a = traitement_click_souris(&event,P_J1,P_J2,P_J3,P_J4,P_buton_V);
					switch(a){
						case 1:
                            /*seletion première case joueurs*/
							S_J1 = SDL_LoadBMP(fond_pseudo_s);
							S_J2 = SDL_LoadBMP(fond_pseudo);
							S_J3 = SDL_LoadBMP(fond_pseudo);
							S_J4 = SDL_LoadBMP(fond_pseudo);
							break;
						case 2:
                            /*seletion deuxième case joueurs*/
							S_J1 = SDL_LoadBMP(fond_pseudo);
							S_J2 = SDL_LoadBMP(fond_pseudo_s);
							S_J3 = SDL_LoadBMP(fond_pseudo);
							S_J4 = SDL_LoadBMP(fond_pseudo);
							break;
						case 3:
                            /*seletion troisième case joueurs*/
							S_J1 = SDL_LoadBMP(fond_pseudo);
							S_J2 = SDL_LoadBMP(fond_pseudo);
							S_J3 = SDL_LoadBMP(fond_pseudo_s);
							S_J4 = SDL_LoadBMP(fond_pseudo);
							break;
						case 4:
                            /*seletion quatrième case joueurs*/
							S_J1 = SDL_LoadBMP(fond_pseudo);
							S_J2 = SDL_LoadBMP(fond_pseudo);
							S_J3 = SDL_LoadBMP(fond_pseudo);
							S_J4 = SDL_LoadBMP(fond_pseudo_s);
							break;
                        case 5:
                            /*seletion bouton validé case joueurs*/
                            init_j_lauch = SDL_FALSE;
                            break;
						default:
                            /*remise a 0 de la selction des case joueurs*/
							S_J1 = SDL_LoadBMP(fond_pseudo);
							S_J2 = SDL_LoadBMP(fond_pseudo);
							S_J3 = SDL_LoadBMP(fond_pseudo);
							S_J4 = SDL_LoadBMP(fond_pseudo);
							break;
					}
					break;
                /*evement si touche clavièr appyuers*/
				case SDL_KEYDOWN:
					c = recuperation_texte(event);/*recuperation du texte Maj ou non, num , ? si touche suppr*/
 					switch(a){
						case 1:
							modification_chaine(Noms_joueurs[0],c);
							Nom_J1 = TTF_RenderText_Blended(police,Noms_joueurs[0], Noire);
							break;
						case 2:
							modification_chaine(Noms_joueurs[1],c);
							Nom_J2 = TTF_RenderText_Blended(police,Noms_joueurs[1], Noire);
							break;
						case 3:
							modification_chaine(Noms_joueurs[2],c);
							Nom_J3 = TTF_RenderText_Blended(police,Noms_joueurs[2], Noire);
							break;
						case 4:
							modification_chaine(Noms_joueurs[3],c);
							Nom_J4 = TTF_RenderText_Blended(police,Noms_joueurs[3], Noire);
							break;
						default:
							break;							
					}
					break;	
                /*evenement touche relaché pour prendre en compte la majuscule*/
				case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_RSHIFT){
                        Majusucle=0;  
                    }
                    break;
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
                    quit = -1;
					break;
				default:
					break;
		    }
            /*Actualisation de tout les elements suseptible d'avoir était modifier*/
            SDL_BlitSurface(S_J1, NULL,fenetre, &P_J1);
            SDL_BlitSurface(S_J2, NULL,fenetre, &P_J2);
            SDL_BlitSurface(S_J3, NULL,fenetre, &P_J3);
            SDL_BlitSurface(S_J4, NULL,fenetre, &P_J4);
            SDL_BlitSurface(Nom_J1, NULL,fenetre, &P_t_J1);
            SDL_BlitSurface(Nom_J2, NULL,fenetre, &P_t_J2);
            SDL_BlitSurface(Nom_J3, NULL,fenetre, &P_t_J3);
            SDL_BlitSurface(Nom_J4, NULL,fenetre, &P_t_J4);
            SDL_BlitSurface(Buton_V, NULL,fenetre, &P_buton_V);
            SDL_BlitSurface(Texte_V, NULL,fenetre, &P_t_v);
            SDL_Flip(fenetre);
        }
    }
    
    /*verification que 2 joueur nes pas le meme nom et modification si nessecaire et quelle ne sont pas vide*/
    verification_chaine_id(Noms_joueurs);

	/*Liberation de toute la mémoire*/
    TTF_CloseFont(police);
    TTF_CloseFont(police_tt);
    TTF_Quit();
    
    /*liberation des surface*/ 
    SDL_FreeSurface(fenetre);
    SDL_FreeSurface(S_J1);
    SDL_FreeSurface(S_J2);
    SDL_FreeSurface(S_J3);
    SDL_FreeSurface(S_J4);
    SDL_FreeSurface(Nom_J1);
    SDL_FreeSurface(Nom_J2); 
    SDL_FreeSurface(Nom_J3); 
    SDL_FreeSurface(Nom_J4);
    SDL_FreeSurface(Title);  
    SDL_FreeSurface(Buton_V);
    SDL_FreeSurface(Texte_V);
    SDL_FreeSurface(image_d1);
    SDL_FreeSurface(image_d2);
    SDL_FreeSurface(image_d3);
    SDL_FreeSurface(image_d4);
   
    /*fermeture de la SDL*/
    SDL_Quit();
    
   return quit;
}

/*recuperation du texte, ? si touche suppr*/
int meme(char *nom1,char *nom2){
    int i=strcmp(nom1,nom2);   
    if(i==0)
        return 1;
    else
        return 0;
}

/*Fct qui remplace une chaine vide par joueur_X*/
char recuperation_texte(SDL_Event event){
    char c;
	if(event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z'){
		if(Majusucle == 1){
			c = event.key.keysym.sym -'a' + 'A';
		}
		else{
			c = event.key.keysym.sym;
		}
	}
	else{
		switch(event.key.keysym.sym){
			case SDLK_KP0:
				c='0';
				break;
			case SDLK_KP1:
				c='1';
				break;
			case SDLK_KP2:
				c='2';
				break;
			case SDLK_KP3:
				c='3';
				break;
			case SDLK_KP4:
				c='4';
				break;
			case SDLK_KP5: 
				c='5';
				break;
			case SDLK_KP6:
				c='6';
				break;
			case SDLK_KP7:
				c='7';
				break;
			case SDLK_KP8:
				c='8';
				break;
			case SDLK_KP9:
				c='9';
				break;
			case SDLK_SPACE: 
				c='_';
				break;
			case SDLK_BACKSPACE:
				c='?';
				break;
			default:
				c='\0';
				break;
		}
	}
    Majusucle =0;
    if(event.key.keysym.sym == SDLK_RSHIFT || event.key.keysym.sym == SDLK_RSHIFT){
        Majusucle =1;  
    }
    return c;
}

/*permet d'ajouter ou d'enlever des caractères a partir de recuperation_texte*/
void chaine_non_vide(char* pseudo, int i){
    if(strlen(pseudo)==0){
        sprintf(pseudo,"Joueur_%d",i);
    } 
}

/*fct qui configure un SDL_Rect avec x et y*/
void modification_chaine(char *pseudo, char c){
	if(c == '?'){
		int i = strlen(pseudo);
        if(i>0)
		    pseudo[i-1]='\0';
	}
	else{
        if(strlen(pseudo)<TAILLE_NOM_JOUEUR-1){
            char temp[2];
            temp[0]=c;
            temp[1]='\0';
            strcat(pseudo,temp);
        }
	}
}

/*Fct qui modifie les pseudos pour qu'il ne soit pas identique ou vide*/
void creation_pos(SDL_Rect *Position, int x,int y){
		Position->x = x;
		Position->y = y;
}

/*fct principale qui lance la fenetre graphique et récupére les noms des 4 joueurs*/
void verification_chaine_id(char Noms_joueurs[][TAILLE_NOM_JOUEUR]){
    int i,j;
    for(j=3;j>=1;j--){
        for(i=3;i>=0;i--){
            if(j!=i){
                if(meme(Noms_joueurs[j],Noms_joueurs[i])){
                    Noms_joueurs[j][0]='\0';   
                }
            }
        }
    }
    
    for(i=0; i<4;i++){
        chaine_non_vide(Noms_joueurs[i], i+1);
    }
}

/*fct qui verifie si le click de la souris est dans la zone definie*/
int verification_zone(SDL_Event *event, int position_x, int position_y, int largeur, int longueur){
	/*Retourne 1 si le clik souris est dans le zone  */
	if(event->button.x > position_x && event->button.x < position_x + largeur && event->button.y > position_y && event->button.y < position_y + longueur){
			return 1;
		}
	else
		return 0;
}

/*Fct qui indique quelle zone notable de la fenetre est selectionée*/
int traitement_click_souris(SDL_Event *event,SDL_Rect P_J1, SDL_Rect P_J2, SDL_Rect P_J3, SDL_Rect P_J4, SDL_Rect P_buton_V){
	/*renvoie 0 si touche a coté, 1 si case j1 2 si j2 etc , 5 si bouton terminier * -1 si pas de chagmeent nesesaire*/	
	if (event->button.button == SDL_BUTTON_LEFT){
		if(verification_zone(event,P_J1.x ,P_J1.y ,186,31) == 1){
			return 1;
		}
		else if(verification_zone(event,P_J2.x ,P_J2.y ,186,31) == 1){
			return 2;
		}
		else if(verification_zone(event,P_J3.x ,P_J3.y ,186,31) == 1){
			return 3;
		}
		else if(verification_zone(event,P_J4.x ,P_J4.y ,186,31) == 1){
			return 4;
		}
        else if(verification_zone(event,P_buton_V.x ,P_buton_V.y ,150,50) == 1){
			return 5;
		}
		else{
			return 0;
		}
	}
	else{
		return -1;
	}
}
