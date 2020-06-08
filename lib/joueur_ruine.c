#include "joueur_ruine.h"


/*fct qui affiche que le joueur n'a pas de carte sortie de prison*/
int pas_de_carte(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    int retour;
    
    /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *b_btn = NULL;
    SDL_Surface *t_btn = NULL;
    
    SDL_Rect p_b_btn;
    SDL_Rect p_t_btn;

    /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 155, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Vendre carte sortie de prison", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    t_btn = TTF_RenderText_Blended(police,"Vous n'avez pas de carte sortie de prison", Noire);
    
    /*initialisation des bouttons*/
    b_btn = SDL_CreateRGBSurface(SDL_HWSURFACE, t_btn->w+10,t_btn->h+10,32,0,0,0,0);
    SDL_FillRect(b_btn,NULL,SDL_MapRGB(b_btn->format,239,243,73)); 
    
    /*initialisation poistion des boutons*/
    p_b_btn.x = fenetre->w/2 - b_btn->w/2;
    p_b_btn.y = fenetre->h/2 - b_btn->h/2;
    
    /*initialisation position texte*/
    p_t_btn.x = p_b_btn.x+5;
    p_t_btn.y = p_b_btn.y+5;
   
    
    /*Blitage et actualisation de l'écran*/
    SDL_BlitSurface(b_btn, NULL, fenetre, &p_b_btn);
    
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
					if(verification_zone(&event,p_b_btn.x ,p_b_btn.y ,b_btn->w,b_btn->h) == 1){
                        retour = 1;  
                        init_j_lauch = SDL_FALSE;
                    }
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
					break;
				default:
					break;
			}
		}
    }
		
    SDL_FreeSurface(b_btn);

    SDL_FreeSurface(t_btn);

    SDL_Quit();
    return retour;
}

/*Demande la validation (retour=1) ou le refus (retour=0) pour vendre la carte*/
int vendre_carte(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    int retour;
    
    /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *b_Accepter = NULL, *b_Refuser = NULL,  *b_txt = NULL;
    SDL_Surface *t_Accepter = NULL, *t_Refuser = NULL, *t_txt = NULL;
    
    SDL_Rect p_b_A, p_b_R, p_b_t ;
    SDL_Rect p_t_A, p_t_R, p_t_t;

    /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 255, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Vendre carte sortie prison", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    t_Accepter  = TTF_RenderText_Blended(police,"Accepter", Noire);
    t_Refuser = TTF_RenderText_Blended(police,"Refuser", Noire);
    t_txt = TTF_RenderText_Blended(police,"Vendre votre carte ?", Noire);
    
    /*initialisation des bouttons*/
    b_Accepter = SDL_CreateRGBSurface(SDL_HWSURFACE, t_Accepter->w+10,t_Accepter->h+10,32,0,0,0,0);
    SDL_FillRect(b_Accepter,NULL,SDL_MapRGB(b_Accepter->format,239,243,73)); 
    
    b_Refuser = SDL_CreateRGBSurface(SDL_HWSURFACE, t_Refuser->w+10, t_Refuser->h+10,32,0,0,0,0);
    SDL_FillRect(b_Refuser,NULL,SDL_MapRGB(b_Refuser->format,239,243,73));    
    
    b_txt = SDL_CreateRGBSurface(SDL_HWSURFACE, t_txt->w+10, t_txt->h+10,32,0,0,0,0);
    SDL_FillRect(b_txt,NULL,SDL_MapRGB( t_txt->format,239,243,73));
    
    /*initialisation poistion des boutons*/
    p_b_t.x = fenetre->w/2 - b_txt->w/2;
    p_b_t.y = 25;
        
    p_b_A.x = fenetre->w/2 - b_Accepter->w/2;
    p_b_A.y = p_b_t.y + b_Accepter->h + 40;
        
    p_b_R.x = fenetre->w/2 - b_Refuser->w/2;
    p_b_R.y = p_b_A.y + b_Refuser->h + 40;
    
    /*initialisation position texte*/
    p_t_A.x = p_b_A.x+5;
    p_t_A.y = p_b_A.y+5;
    
    p_t_R.x = p_b_R.x+5;
    p_t_R.y = p_b_R.y+5;
    
    p_t_t.x = p_b_t.x+5;
    p_t_t.y = p_b_t.y+5;
    
    
    /*Blitage et actualisation de l'écran*/
    SDL_BlitSurface(b_Accepter, NULL, fenetre, &p_b_A);
    SDL_BlitSurface(b_Refuser, NULL, fenetre, &p_b_R);
    SDL_BlitSurface(b_txt, NULL, fenetre, &p_b_t);
    
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
                        retour = 0;  
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
    SDL_FreeSurface(b_txt);
    SDL_FreeSurface(t_Accepter);
    SDL_FreeSurface(t_Refuser);
    SDL_FreeSurface(t_txt);
    SDL_Quit();
    return retour;
}

/*listing et selection d'une terrain apartenant au joueur et ayant une maison"joueur_choisie"*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain => confirmation =-1*/
int choix_proprietes_maison(PLATEAU *plateau, int joueur_choisie){
    int retour;
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *terrain[40];
    
    SDL_Rect p_terrain[40];
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(550, 350, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Choisissez un terrain", NULL);
    
        /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Couleur_t[11];
    
    creation_couleur(Couleur_t,0, 88, 41, 0);       /*marron*/
    creation_couleur(Couleur_t,1, 0, 255, 255);     /*cyan*/
    creation_couleur(Couleur_t,2, 255, 0, 255);     /*magenta*/
    creation_couleur(Couleur_t,3, 237, 127, 16);    /*orange*/
    creation_couleur(Couleur_t,4, 255, 0, 0);       /*rouge*/
    creation_couleur(Couleur_t,5, 232, 214, 48);    /*jaune*/
    creation_couleur(Couleur_t,6, 0, 255, 0);       /*vert*/
    creation_couleur(Couleur_t,7, 0, 0, 255);       /*bleu*/
    creation_couleur(Couleur_t,8, 213, 208, 134);   /*pas de fond*/
    creation_couleur(Couleur_t,9, 213, 208, 134);   /*pas de fond*/
    creation_couleur(Couleur_t,10,213, 208, 134);   /*pas de fond*/
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    int nb_terrain=0,nb_t_valide =0,i,j;
    
    CASE *c;
    for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
        if(c->terrain!=NULL && c->terrain->proprietaire==joueur_choisie && c->terrain->nb_maison>=1){
            terrain[nb_terrain]= TTF_RenderText_Shaded(police,c->terrain->nom, Noire,Couleur_t[c->terrain->couleur]);
            nb_t_valide++;
        } else {
            terrain[nb_terrain]=NULL;
        }
        nb_terrain++;
    }
    
    
    /*initialisation position*/
    int y=10, x=10;
    i=0,j=0;
    while(i<nb_terrain){
        if(terrain[i]!=NULL){
            if(j==10 || j == 20){
                x=x+175;
                y=10;
            }
            p_terrain[i].x=x;
            p_terrain[i].y=y;
            y=y+35;
            j++;
           
        }
        i++;
    }
    
     /*Blitage et actualisation de l'écran*/
    i=0;
    while(i<nb_terrain){
         if(terrain[i]!=NULL){
            SDL_BlitSurface(terrain[i], NULL, fenetre, &p_terrain[i]);
         }
         i++;
    }
        
    SDL_Flip(fenetre);
    
    SDL_bool init_j_lauch = SDL_TRUE;
    
    if(nb_t_valide == 0){
        init_j_lauch = SDL_FALSE; /*pas de terrain on sort directement*/
        retour = 0;
    }
    
    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    i=0;
                    while(i<nb_terrain){
                         if(terrain[i]!=NULL){
                            if(verification_zone(&event,p_terrain[i].x ,p_terrain[i].y,terrain[i]->w,terrain[i]->h) == 1){
                                if(i<=nb_terrain){ 
                                    retour = i+2;  
                                    init_j_lauch = SDL_FALSE;
                                }
                            }
                            
                         }
                        i++;
                    }
                    break;
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
                    retour=-1;
					break;
				default:
					break;
			}
		}
    }
    i=0;
    while(i<nb_terrain){
        if (terrain[i]!=NULL){
            SDL_FreeSurface(terrain[i]);
        }
        i++;
    }
    SDL_Quit();
    return retour;
}

/*Listing du nombre de maison(s) et hotel du terrain choisit "terrain_choi" du joueur "joueur_courant"*/
int choix_maisons(PLATEAU *plateau, int joueur_courant, int terrain_choi){
    int retour;
    char tempory_string[30];
    int nb_hotel=0, nb_mais=0;
    
    nb_mais = nb_maisons(terrain_choi, plateau);
    
    if(nb_mais==5){
        nb_mais=4;
        nb_hotel=1;
    }
        
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *maison[5];
    
    
    SDL_Rect p_maison[5];
;
    
        /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
            /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
      
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 255, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Vendre maison(s) / Hotel", NULL);


    /*initialisation du texte*/
    int nb_maison=0,i;
    for(i=0; i<=3;i++){
        if(i<nb_mais){
            sprintf(tempory_string, "%d Maison(s)", i+1);
            maison[nb_maison]= TTF_RenderText_Blended(police,tempory_string, Noire);
            nb_maison++;
        }
    }
    if(nb_hotel!=0){
            sprintf(tempory_string, "Hotel");
            maison[nb_maison]= TTF_RenderText_Blended(police,tempory_string, Noire);
            nb_maison++;
    }
    
 
    /*initialisation position*/
    int y=50;
    i=0;
    while(i<nb_mais){
        p_maison[i].x=fenetre->w/2 - maison[i]->w/2;
        p_maison[i].y=y+i*y;
        i++;
    }
    if(nb_hotel!=0){
        p_maison[i].x=fenetre->w/4 - maison[i]->w/2;
        p_maison[i].y=fenetre->h/2 - maison[i]->h/2;
    }

   
     /*Blitage et actualisation de l'écran*/
    i=0;
    while(i<nb_maison){
        SDL_BlitSurface(maison[i], NULL, fenetre, &p_maison[i]);
        i++;
    }

        
    SDL_Flip(fenetre);
    
    SDL_bool init_j_lauch = SDL_TRUE;
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                   
                    if(verification_zone(&event,p_maison[0].x ,p_maison[0].y,maison[0]->w,maison[0]->h) == 1){
                        if(nb_maison>=1){ 
                            retour = 0;  
                            init_j_lauch = SDL_FALSE;
                        }
                    }
                    
                    if(nb_mais>1 && nb_maison>1){
                        if(verification_zone(&event,p_maison[1].x ,p_maison[1].y,maison[1]->w,maison[1]->h) == 1){
                            if(nb_maison>=2){ 
                                retour = 1;  
                                init_j_lauch = SDL_FALSE;
                            }
                        }
                    }
                    
                    if(nb_mais>2 && nb_maison>2){
                        if(verification_zone(&event,p_maison[2].x ,p_maison[2].y,maison[2]->w,maison[2]->h) == 1){

                            if(nb_maison>=3){ 
                                retour = 2;  
                                init_j_lauch = SDL_FALSE;
                            }
                        }
                    }
                    if(nb_mais>3 && nb_maison>3){
                        if(verification_zone(&event,p_maison[3].x ,p_maison[3].y,maison[3]->w,maison[3]->h) == 1){
                                if(nb_maison>=4){ 
                                    retour = 3;  
                                    init_j_lauch = SDL_FALSE;
                                }
                            }
                    }
                    
                    if(nb_hotel!=0 && nb_maison>4){
                        if(verification_zone(&event,p_maison[4].x ,p_maison[4].y,maison[4]->w,maison[4]->h) == 1){
                            if(nb_maison>=5){
                                retour = 4;  
                                init_j_lauch = SDL_FALSE;
                            }
                        }
                    }
                   
                    break; 
				default:
					break;
			}
		}
    }
  
    for(i=0; i<nb_mais+nb_hotel;i++){
        if(maison[i]!=NULL) {
            SDL_FreeSurface(maison[i]);
        }
    }
    SDL_Quit();
    if (confirmation_maison(plateau,retour+1,terrain_choi,prix_construction(terrain_choi,plateau))==1){
        return retour+1;
    }
    return -1;
}

/*fct qui demande confirmatuon la proposition pour la vente "de nb_mai" maisons, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int confirmation_maison(PLATEAU *plateau, int nb_mai, int terrain, int prix){
    int retour;
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *texte_terrain=NULL, *texte_prix=NULL, *texte=NULL;
    SDL_Surface *bouton_v=NULL, *t_valider=NULL;
    SDL_Surface *bouton_r=NULL, *t_refuser=NULL;
    
    SDL_Rect p_t_t, p_t_p, p_t, p_t_v, p_t_r;
    SDL_Rect p_b_r, p_b_v;
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(525, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Confirmation ?", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Blanc = {255,255,255};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*Création du bouton*/
    bouton_v = SDL_LoadBMP(buton);
    bouton_r = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(bouton_v,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_v->format,255,255,255));
    SDL_SetColorKey(bouton_r,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_r->format,255,255,255));
    
    /*ajout texte bouton*/
    t_valider = TTF_RenderText_Blended(police,"Valider", Blanc);
    t_refuser = TTF_RenderText_Blended(police,"Refuser", Blanc);
    
    /*Initialisation de la position du bouton et du texte bouton*/
    p_b_v.x= fenetre->w-(bouton_v->w+25);
    p_b_v.y= fenetre->h-(bouton_v->h+25);
    
    p_b_r.x= 10/*(bouton_r->w+50) - p_b_v.x*/ ;
    p_b_r.y= p_b_v.y;
    
    p_t_v.x= p_b_v.x+bouton_v->w/2-t_valider->w/2;
    p_t_v.y= p_b_v.y+bouton_v->h/2-t_valider->h/2;
    
    p_t_r.x= p_b_r.x+bouton_r->w/2-t_refuser->w/2;
    p_t_r.y= p_b_r.y+bouton_r->h/2-t_refuser->h/2;
    
    /*recuperation du terrain , joueur et prix*/
    char tempory_string[60];


    if (nb_mai==5) sprintf(tempory_string, "%d Hotel", 1);
    else sprintf(tempory_string, "%d Maisons", nb_mai);
    texte_terrain = TTF_RenderText_Blended(police,tempory_string, Noire);

    if (nb_mai!=5) prix=prix*nb_mai;
    sprintf(tempory_string, "Prix : %d pp", prix);
    texte_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
    
    /*initialisation du texte*/
    texte = TTF_RenderText_Blended(police,"Recapitulatif de la vente : ", Noire);
    
    /*Positionement des textes*/
    p_t.x= 10;
    p_t.y= 10;
        
    p_t_t.x = 50;
    p_t_t.y = p_t.y +25;
    
    p_t_p.x = 50;
    p_t_p.y = p_t_t.y +25;
    
    /*Blitage et actualisation de l'écran*/    
    SDL_BlitSurface(texte, NULL, fenetre, &p_t); 
    SDL_BlitSurface(texte_terrain, NULL, fenetre, &p_t_t); 
    SDL_BlitSurface(texte_prix, NULL, fenetre, &p_t_p); 
 
      
    SDL_BlitSurface(bouton_v, NULL, fenetre, &p_b_v);   
    SDL_BlitSurface(t_valider, NULL, fenetre, &p_t_v);
    
    SDL_BlitSurface(bouton_r, NULL, fenetre, &p_b_r);   
    SDL_BlitSurface(t_refuser, NULL, fenetre, &p_t_r); 
    SDL_Flip(fenetre);
    
    /*boucle programme*/
    SDL_bool init_j_lauch = SDL_TRUE;

    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    if(verification_zone(&event,p_b_v.x ,p_b_v.y,bouton_v->w,bouton_v->h) == 1){
                        retour = 1;   
                        init_j_lauch = SDL_FALSE;
                    }
                    else if(verification_zone(&event,p_b_r.x ,p_b_r.y,bouton_r->w,bouton_r->h) == 1){
                        retour = -1;
                        init_j_lauch = SDL_FALSE;
                    }
                    break;	
				default:
					break;
			}
		}
    }

    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte_terrain);
    SDL_FreeSurface(texte_prix);
    SDL_FreeSurface(bouton_v);
    SDL_FreeSurface(bouton_r);
    SDL_FreeSurface(t_valider);
    SDL_FreeSurface(t_refuser);
    

    return retour;
    
    
    
}

/*Fonction qui retourne le nombre de maison a vendre en fonction du bouton sur lequel on a appuyer "val_retour"*/
int identification_maison(int val_retour, int joueur_courant){
    switch(joueur_courant){
        case 0:
            return val_retour+1;
            break;
        case 1:
            if(val_retour>=1)
                return val_retour+1;
            else
                return val_retour;
            break;
        case 2:
            if(val_retour>=2)
                return val_retour+1;
            else
                return val_retour;
            break;
        case 3:
            return val_retour;
            break;
        default:
			break;
    }
   return -1;
}

/*/*listing et selection d'une terrain apartenant au joueur et pouvant etre hypothequer*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain => confirmation =-1*/
int choix_proprietes_hypotheque(PLATEAU *plateau, int joueur_choisie){
    int retour;
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *terrain[40];
    
    SDL_Rect p_terrain[40];
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(550, 350, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Choisissez un terrain", NULL);
    
        /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Couleur_t[11];
    
    creation_couleur(Couleur_t,0, 88, 41, 0);       /*marron*/
    creation_couleur(Couleur_t,1, 0, 255, 255);     /*cyan*/
    creation_couleur(Couleur_t,2, 255, 0, 255);     /*magenta*/
    creation_couleur(Couleur_t,3, 237, 127, 16);    /*orange*/
    creation_couleur(Couleur_t,4, 255, 0, 0);       /*rouge*/
    creation_couleur(Couleur_t,5, 232, 214, 48);    /*jaune*/
    creation_couleur(Couleur_t,6, 0, 255, 0);       /*vert*/
    creation_couleur(Couleur_t,7, 0, 0, 255);       /*bleu*/
    creation_couleur(Couleur_t,8, 213, 208, 134);   /*pas de fond*/
    creation_couleur(Couleur_t,9, 213, 208, 134);   /*pas de fond*/
    creation_couleur(Couleur_t,10,213, 208, 134);   /*pas de fond*/
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    int nb_terrain=0,nb_t_valide =0,i,j;
    CASE *c;
    for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
        if(c->terrain!=NULL && c->terrain->proprietaire==joueur_choisie && c->terrain->nb_maison==0){
            terrain[nb_terrain]= TTF_RenderText_Shaded(police,c->terrain->nom, Noire,Couleur_t[c->terrain->couleur]);
            nb_t_valide++;
        } else {
            terrain[nb_terrain]=NULL;
        }
        nb_terrain++;
    }
     
    /*initialisation position*/
    int y=10, x=10;
    i=0,j=0;
    while(i<nb_terrain){
        if(terrain[i]!=NULL){
            if(j==10 || j == 20){
                x=x+175;
                y=10;
            }
            p_terrain[i].x=x;
            p_terrain[i].y=y;
            y=y+35;
            j++;
           
        }
        i++;
    }
    
     /*Blitage et actualisation de l'écran*/
    i=0;
    while(i<nb_terrain){
         if(terrain[i]!=NULL){
            SDL_BlitSurface(terrain[i], NULL, fenetre, &p_terrain[i]);
         }
         i++;
    }
        
    SDL_Flip(fenetre);
    
    SDL_bool init_j_lauch = SDL_TRUE;
    
    if(nb_t_valide == 0){
        init_j_lauch = SDL_FALSE; /*pas de terrain on sort directement*/
        retour = 0;
    }
    
    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    i=0;
                    while(i<nb_terrain){
                         if(terrain[i]!=NULL){
                            if(verification_zone(&event,p_terrain[i].x ,p_terrain[i].y,terrain[i]->w,terrain[i]->h) == 1){
                                if(i<=nb_terrain){ 
                                    retour = i+2;  
                                    init_j_lauch = SDL_FALSE;
                                }
                            }
                            
                         }
                         i++;
                    }
                    break;
				case SDL_QUIT:
					init_j_lauch = SDL_FALSE;
					break;
				default:
					break;
			}
		}
    }
    i=0;
    while(i<nb_terrain){
        if (terrain[i]!=NULL){
            SDL_FreeSurface(terrain[i]);
        }
        i++;
    }
    SDL_Quit();
    if (retour>0 && confirmation_hypotheque(plateau,joueur_choisie,retour,valeur_hypothequaire(retour,plateau))==1){
        return retour;
    }
    return -1;
}


/*fct qui demande confirmatuon la proposition pour l'achat d'un terraint T, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int confirmation_hypotheque(PLATEAU *plateau, int joueur, int terrain, int prix){
    int retour;
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *texte_terrain=NULL, *texte_prix=NULL, *texte=NULL;
    SDL_Surface *bouton_v=NULL, *t_valider=NULL;
    SDL_Surface *bouton_r=NULL, *t_refuser=NULL;
    
    SDL_Rect p_t_t, p_t_p, p_t, p_t_v, p_t_r;
    SDL_Rect p_b_r, p_b_v;
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(525, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Confirmation ?", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Blanc = {255,255,255};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*Création du bouton*/
    bouton_v = SDL_LoadBMP(buton);
    bouton_r = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(bouton_v,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_v->format,255,255,255));
    SDL_SetColorKey(bouton_r,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_r->format,255,255,255));
    
    /*ajout texte bouton*/
    t_valider = TTF_RenderText_Blended(police,"Valider", Blanc);
    t_refuser = TTF_RenderText_Blended(police,"Refuser", Blanc);
    
    /*Initialisation de la position du bouton et du texte bouton*/
    p_b_v.x= fenetre->w-(bouton_v->w+25);
    p_b_v.y= fenetre->h-(bouton_v->h+25);
    
    p_b_r.x= 10/*(bouton_r->w+50) - p_b_v.x*/ ;
    p_b_r.y= p_b_v.y;
    
    p_t_v.x= p_b_v.x+bouton_v->w/2-t_valider->w/2;
    p_t_v.y= p_b_v.y+bouton_v->h/2-t_valider->h/2;
    
    p_t_r.x= p_b_r.x+bouton_r->w/2-t_refuser->w/2;
    p_t_r.y= p_b_r.y+bouton_r->h/2-t_refuser->h/2;
    
    /*recuperation du terrain , joueur et prix*/
    int i;
    char tempory_string[60];
    
    CASE *c;
    c=plateau->case_depart;
    for(i=1;i<terrain;i++){
        c=c->suivante; 
    }
    
    sprintf(tempory_string, "Terrain : %s", c->nom);
    texte_terrain = TTF_RenderText_Blended(police,tempory_string, Noire);

    sprintf(tempory_string, "Prix : %d pp", prix);
    texte_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
    
    /*initialisation du texte*/
    texte = TTF_RenderText_Blended(police,"Recapitulatif de l'hypotheque : ", Noire);
    
    /*Positionement des textes*/
    p_t.x= 10;
    p_t.y= 10;
        
    p_t_t.x = 50;
    p_t_t.y = p_t.y +25;
    
    p_t_p.x = 50;
    p_t_p.y = p_t_t.y +25;
    
    /*Blitage et actualisation de l'écran*/    
    SDL_BlitSurface(texte, NULL, fenetre, &p_t); 
    SDL_BlitSurface(texte_terrain, NULL, fenetre, &p_t_t); 
    SDL_BlitSurface(texte_prix, NULL, fenetre, &p_t_p); 
 
      
    SDL_BlitSurface(bouton_v, NULL, fenetre, &p_b_v);   
    SDL_BlitSurface(t_valider, NULL, fenetre, &p_t_v);
    
    SDL_BlitSurface(bouton_r, NULL, fenetre, &p_b_r);   
    SDL_BlitSurface(t_refuser, NULL, fenetre, &p_t_r); 
    SDL_Flip(fenetre);
    
    /*boucle programme*/
    SDL_bool init_j_lauch = SDL_TRUE;

    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    if(verification_zone(&event,p_b_v.x ,p_b_v.y,bouton_v->w,bouton_v->h) == 1){
                        retour = 1;   
                        init_j_lauch = SDL_FALSE;
                    }
                    else if(verification_zone(&event,p_b_r.x ,p_b_r.y,bouton_r->w,bouton_r->h) == 1){
                        retour = -1;
                        init_j_lauch = SDL_FALSE;
                    }
                    break;	
				default:
					break;
			}
		}
    }

    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte_terrain);
    SDL_FreeSurface(texte_prix);
    SDL_FreeSurface(bouton_v);
    SDL_FreeSurface(bouton_r);
    SDL_FreeSurface(t_valider);
    SDL_FreeSurface(t_refuser);
    

    return retour;
    
    
    
}

