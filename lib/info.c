#include "info.h"



/***Fonction qui crée une fenetre indiquant au joueur courant qu'il a perdu (=plus d'argent, plus de terrain,...)***/
void perdu(PLATEAU *plateau, int joueur){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    char tempory[30];
    
    /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *t_btn = NULL;
    
    SDL_Rect p_t_btn;

    /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 155, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Défaite", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 30);
    
    /*initialisation du texte*/
    sprintf(tempory,"%s a  perdu",plateau->joueurs[joueur]->nom);
    t_btn = TTF_RenderText_Blended(police,tempory, Noire);
    
    p_t_btn.x=fenetre->w/2 - t_btn->w/2;
    p_t_btn.y=fenetre->h/2 - t_btn->h/2; 
    
    /*Blitage et actualisation de l'écran*/
  
    SDL_BlitSurface(t_btn, NULL, fenetre, &p_t_btn);
    
    SDL_Flip(fenetre);
    
    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
                        init_j_lauch = SDL_FALSE;

				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
					break;
				default:
					break;
			}
		}
    }

    SDL_FreeSurface(t_btn);

    SDL_Quit();
}

/*Fonction qui indique combien le joueur (joueur_courant) doit payer selon la case sur laquelle il se trouve (position) */
void info_payer(PLATEAU *plateau, int joueur_courant , int position){

    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *texte_terrain=NULL, *texte_prix=NULL, *texte_joueur=NULL, *texte=NULL;
    
    SDL_Rect p_t_t, p_t_p, p_t_j,p_t;
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(525, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/

    SDL_WM_SetCaption("Information Payement", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
        
    /*recuperation du terrain , joueur et prix*/
    char tempory_string[60];
    char nom[20]="";
    
    if(position!=5 && position!=39){
        nom_terrain(nom, position, plateau);
        sprintf(tempory_string, "En tombant sur : %s", nom);
        texte_terrain = TTF_RenderText_Blended(police,tempory_string, Noire);
        
        sprintf(tempory_string, "Vous devez : %d pp", loyer(joueur_courant, position, plateau));
        texte_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
        
        nom_joueur(nom,proprietaire_terrain(position, plateau), plateau);
        sprintf(tempory_string, "A : %s", nom);
        texte_joueur = TTF_RenderText_Blended(police,tempory_string, Noire);
    }
    else{
        nom_terrain(nom, position, plateau);
        sprintf(tempory_string, "En tombant sur : %s", nom);
        texte_terrain = TTF_RenderText_Blended(police,tempory_string, Noire);
        
        if (position==5) {
            sprintf(tempory_string, "Vous avez payez : %d pp",200);
        } else {
            sprintf(tempory_string, "Vous avez payez : %d pp",100);
        }
        texte_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
        
        texte_joueur = TTF_RenderText_Blended(police,"", Noire);
    }
    
    /*initialisation du texte*/
    texte = TTF_RenderText_Blended(police,"Recapitulatif de la transaction : ", Noire);
    
    /*Positionement des textes*/
    p_t.x= 10;
    p_t.y= 10;
    
    p_t_t.x = 50;
    p_t_t.y = p_t.y +30;
           
    p_t_p.x = 50;
    p_t_p.y = p_t_t.y +25;
    
    p_t_j.x = 50;
    p_t_j.y = p_t_p.y +25;
    
    /*Blitage et actualisation de l'écran*/    
    SDL_BlitSurface(texte, NULL, fenetre, &p_t); 
    SDL_BlitSurface(texte_terrain, NULL, fenetre, &p_t_t); 
    SDL_BlitSurface(texte_prix, NULL, fenetre, &p_t_p); 
    SDL_BlitSurface(texte_joueur, NULL, fenetre, &p_t_j); 
      
    SDL_Flip(fenetre);
    
    /*boucle programme*/
    SDL_bool init_j_lauch = SDL_TRUE;

    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                        init_j_lauch = SDL_FALSE;
                    break;
                    case SDL_QUIT:
                        init_j_lauch = SDL_FALSE;
					break;
				default:
					break;
			}
		}
    }

    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte_terrain);
    SDL_FreeSurface(texte_prix);
    SDL_FreeSurface(texte_joueur);

  
}

/* Fonction d'affichage du joueur gagnant */
void victoire(PLATEAU *plateau, int joueur){
    char tempory[20];
	/*Initialisation de la SDL*/
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

	/*Creation des Surface*/
    SDL_Surface *fenetre = NULL;
	SDL_Surface *b_terminer= NULL;
	SDL_Surface *t_terminer,*texte1[3], *texte2 = NULL;
	SDL_Surface *image[3], *image_i[3];
	
	/*Creation des positions*/
	SDL_Rect p_b_terminer, p_t_terminer,p_texte1, p_texte2;
	SDL_Rect p_i, p_i_n;
	
	/*Création de la fenetre*/
	fenetre = SDL_SetVideoMode(800, 300, 32, SDL_HWSURFACE);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134));
    SDL_WM_SetCaption("Victore", NULL);

	/*initialisation des police*/
    TTF_Font *police = NULL,*police_tt = NULL;
    police = TTF_OpenFont(POLICE, 24);
    police_tt = TTF_OpenFont(POLICE_lb, 40);
    
    SDL_Color C_texte[3];
	SDL_Color Blanc ={255,255,255};
	creation_couleur(C_texte, 0, 0, 0, 0);		/*noire*/
	creation_couleur(C_texte, 1, 255, 0, 0);	/*jaune*/
	creation_couleur(C_texte, 2, 255, 255, 0);	/*rouge*/
	

	/*creation des image gif*/
	image[0] = SDL_LoadBMP(c1);
	image[1] = SDL_LoadBMP(c2);
	image[2] = SDL_LoadBMP(c3);
	
	image_i[0] = SDL_LoadBMP(ci1);
	image_i[1] = SDL_LoadBMP(ci2);
	image_i[2] = SDL_LoadBMP(ci3);

	/*surppression_fond*/
	int i;
	
	/*position image*/
	p_i.x =0 ;
	p_i.y = 0;
	p_i_n.x = fenetre->w-image_i[0]->w;
	p_i_n.y =0 ;
	
	
	/*recuperation du nom du joueur*/
	nom_joueur(tempory,joueur,plateau);

	/*initialisation du texte*/
	for(i=0; i<3;i++){
		texte1[i] = TTF_RenderText_Blended(police_tt,"Felicitation vous avez gagne",C_texte[i]);
	}

	texte2 = TTF_RenderText_Blended(police,tempory, C_texte[0]);
	t_terminer = TTF_RenderText_Blended(police,"Terminer", Blanc);
		
	 /*Création du bouton*/
    b_terminer = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(b_terminer,SDL_SRCCOLORKEY,SDL_MapRGB(b_terminer->format,255,255,255));
    
	/*initialisation des positions*/
    p_texte1.x = fenetre->w/2-texte1[0]->w/2;
    p_texte1.y = 50;
    p_texte2.x = fenetre->w/2-texte2->w/2;
    p_texte2.y = p_texte1.y+texte1[0]->h+20;

	/*initialisation position bouton*/
	p_b_terminer.x = fenetre->w/2-b_terminer->w/2;
	p_b_terminer.y = fenetre->h-b_terminer->h-20;
	p_t_terminer.x = p_b_terminer.x+b_terminer->w/2-t_terminer->w/2;
	p_t_terminer.y = p_b_terminer.y+b_terminer->h/2-t_terminer->h/2;
   
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(texte1[0], NULL, fenetre, &p_texte1);
    SDL_BlitSurface(texte2, NULL, fenetre, &p_texte2);
	SDL_BlitSurface(b_terminer, NULL, fenetre, &p_b_terminer);
    SDL_BlitSurface(t_terminer, NULL,fenetre, &p_t_terminer);
    SDL_BlitSurface(image[0], NULL,fenetre, &p_i);
    SDL_BlitSurface(image_i[0], NULL,fenetre, &p_i_n);
    
	SDL_Flip(fenetre);

    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
      
	i=0;
	
    while(init_j_lauch){
		SDL_Delay(300);
		i=(i+1)%3;
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,p_b_terminer.x, p_b_terminer.y ,b_terminer->w,b_terminer->h) == 1){
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
					break;
				default:
					break;
			}
		}
		
		SDL_BlitSurface(texte1[i], NULL, fenetre, &p_texte1);
    	SDL_BlitSurface(texte2, NULL, fenetre, &p_texte2);
		SDL_BlitSurface(b_terminer, NULL, fenetre, &p_b_terminer);
    	SDL_BlitSurface(t_terminer, NULL,fenetre, &p_t_terminer);
    	SDL_BlitSurface(image[i], NULL,fenetre, &p_i);
    	SDL_BlitSurface(image_i[i], NULL,fenetre, &p_i_n);
    	SDL_Flip(fenetre);
    }
	
	/*liberation de surface*/
	for(i=0; i<3;i++){
		 SDL_FreeSurface(texte1[i]);
		 SDL_FreeSurface(image[i]);
		 SDL_FreeSurface(image_i[i]);	
	}
    SDL_FreeSurface(texte2);
	SDL_FreeSurface(b_terminer);
    SDL_FreeSurface(t_terminer);
    SDL_Quit();

}

/* Fonction qui demande a l'utilisateur si il veut quitter sans sauvegarder */
int quitter_sauve(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    int retour;
    
    /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *b_Accepter = NULL, *b_Refuser = NULL;
    SDL_Surface *t_Accepter = NULL, *t_Refuser = NULL, *t_txt = NULL;
    
    SDL_Rect p_b_A, p_b_R;
    SDL_Rect p_t_A, p_t_R, p_t_t;

    /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 255, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Quitter ?", NULL);
    
    /*Creation de couleur*/
    SDL_Color Blanc = {255,255,255};
    SDL_Color Noire = {0,0,0};

    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*Création du bouton*/
    b_Accepter = SDL_LoadBMP(buton);
    b_Refuser = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(b_Accepter,SDL_SRCCOLORKEY,SDL_MapRGB(b_Accepter->format,255,255,255));
    SDL_SetColorKey(b_Refuser,SDL_SRCCOLORKEY,SDL_MapRGB(b_Refuser->format,255,255,255));
    
    
    /*initialisation du texte*/
    t_Accepter  = TTF_RenderText_Blended(police,"Accepter", Blanc);
    t_Refuser = TTF_RenderText_Blended(police,"Refuser", Blanc);
    t_txt = TTF_RenderText_Blended(police,"Voulez-vous quitter sans sauvegarder ?", Noire);
    
    
    
    /*initialisation position des boutons*/

    p_b_A.x = fenetre->w/2 - b_Accepter->w/2;
    p_b_A.y = b_Accepter->h + 40;
        
    p_b_R.x = fenetre->w/2 - b_Refuser->w/2;
    p_b_R.y = p_b_A.y + b_Refuser->h + 40;
    
    /*initialisation position texte*/
    p_t_A.x = p_b_A.x+b_Accepter->w/2-t_Accepter->w/2;
    p_t_A.y = p_b_A.y+b_Accepter->h/2-t_Accepter->h/2;
    
    p_t_R.x = p_b_R.x+b_Refuser->w/2-t_Refuser->w/2;
    p_t_R.y = p_b_R.y+b_Refuser->h/2-t_Refuser->h/2;
    
    p_t_t.x = 25;
    p_t_t.y = 25;
    
    
    /*Blitage et actualisation de l'écran*/
    SDL_BlitSurface(b_Accepter, NULL, fenetre, &p_b_A);
    SDL_BlitSurface(b_Refuser, NULL, fenetre, &p_b_R);

    SDL_BlitSurface(t_Accepter, NULL, fenetre, &p_t_A);
    SDL_BlitSurface(t_Refuser, NULL, fenetre, &p_t_R);
    SDL_BlitSurface(t_txt, NULL, fenetre, &p_t_t);
    
    SDL_Flip(fenetre);
    
    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,p_b_A.x ,p_b_A.y ,b_Accepter->w,b_Accepter->h) == 1){
                        retour = 1;  
                        init_j_lauch = SDL_FALSE;
                    }
   					if(verification_zone(&event,p_b_R.x ,p_b_R.y ,b_Refuser->w,b_Refuser->h) == 1){
                        retour = -1;  
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
                    retour = -1;
					break;
				default:
					break;
			}
		}
    }
		
    SDL_FreeSurface(b_Accepter);
    SDL_FreeSurface(b_Refuser);
 
    SDL_FreeSurface(t_Accepter);
    SDL_FreeSurface(t_Refuser);
    SDL_FreeSurface(t_txt);
    SDL_Quit();
    return retour;
}
