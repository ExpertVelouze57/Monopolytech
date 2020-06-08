
#include "fenetre_tt_tour.h"


/*fct qui permets a l'utilisateur de choisir entre lancer les des(3), acheter une maison(2) ou proposer d'acheter u  terraint a un autre joueur(1)*/
int debut_tour(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    int retour;
    
    /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *b_lancer = NULL, *b_achat_m = NULL, *b_achat_t = NULL;
    SDL_Surface *t_lancer = NULL, *t_achat_m = NULL, *t_achat_t = NULL;
    
    SDL_Rect p_b_l, p_b_am, p_b_at;
    SDL_Rect p_t_l, p_t_am,  p_t_at;

    /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 255, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("A vous de jouer", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    t_lancer  = TTF_RenderText_Blended(police,"Lancer les des", Noire);
    t_achat_m = TTF_RenderText_Blended(police,"Acheter une maison", Noire);
    t_achat_t = TTF_RenderText_Blended(police,"Faire une proposition a un autre joueur", Noire);
    
    /*initialisation des bouttons*/
    b_lancer = SDL_CreateRGBSurface(SDL_HWSURFACE, t_lancer->w+10,t_lancer->h+10,32,0,0,0,0);
    SDL_FillRect(b_lancer,NULL,SDL_MapRGB(b_lancer->format,239,243,73)); 
    
    b_achat_m = SDL_CreateRGBSurface(SDL_HWSURFACE, t_achat_m->w+10, t_achat_m->h+10,32,0,0,0,0);
    SDL_FillRect(b_achat_m,NULL,SDL_MapRGB(b_achat_m->format,239,243,73));    
    
    b_achat_t = SDL_CreateRGBSurface(SDL_HWSURFACE, t_achat_t->w+10, t_achat_t->h+10,32,0,0,0,0);
    SDL_FillRect(b_achat_t,NULL,SDL_MapRGB( t_achat_t->format,239,243,73));
    
    /*initialisation poistion des boutons*/
    p_b_l.x = fenetre->w/2 - b_lancer->w/2;
    p_b_l.y = 25;
        
    p_b_am.x = fenetre->w/2 - b_achat_m->w/2;
    p_b_am.y = p_b_l.y + b_lancer->h + 40;
        
    p_b_at.x = fenetre->w/2 - b_achat_t->w/2;
    p_b_at.y = p_b_am.y + b_achat_m->h + 40;
    
    /*initialisation position texte*/
    p_t_l.x = p_b_l.x+5;
    p_t_l.y = p_b_l.y+5;
    
    p_t_am.x = p_b_am.x+5;
    p_t_am.y = p_b_am.y+5;
    
    p_t_at.x = p_b_at.x+5;
    p_t_at.y = p_b_at.y+5;
    
    
    /*Blitage et actualisation de l'écran*/
    SDL_BlitSurface(b_lancer, NULL, fenetre, &p_b_l);
    SDL_BlitSurface(b_achat_m, NULL, fenetre, &p_b_am);
    SDL_BlitSurface(b_achat_t, NULL, fenetre, &p_b_at);
    
    SDL_BlitSurface(t_lancer, NULL, fenetre, &p_t_l);
    SDL_BlitSurface(t_achat_m, NULL, fenetre, &p_t_am);
    SDL_BlitSurface(t_achat_t, NULL, fenetre, &p_t_at);
    
    SDL_Flip(fenetre);
    
    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,p_b_l.x ,p_b_l.y ,b_lancer->w,b_lancer->h) == 1){
                        retour = 3;  
                        init_j_lauch = SDL_FALSE;
                    }
   					if(verification_zone(&event,p_b_am.x ,p_b_am.y ,b_achat_m->w,b_achat_m->h) == 1){
                        retour = 2;  
                        init_j_lauch = SDL_FALSE;
                    }
          			if(verification_zone(&event,p_b_at.x ,p_b_at.y ,b_achat_t->w,b_achat_t->h) == 1){
                        retour = 1;  
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
		
    SDL_FreeSurface(b_lancer);
    SDL_FreeSurface(b_achat_m);
    SDL_FreeSurface(b_achat_t);
    SDL_FreeSurface(t_lancer);
    SDL_FreeSurface(t_achat_m);
    SDL_FreeSurface(t_achat_t);
    SDL_Quit();
    return retour;
}

/********************************/
/*fct proposition achat terraint*/
/********************************/
/*aucun retour, les données sont placees dans les 4 derniers parametres joueur(0->3), terrain(1->40), prix et validation(1 ok, -1pas ok)*/
void proposition_achat_terrain(PLATEAU *plateau,int joueur_courant,int *joueur, int *terrain, int *prix, int* validation){
    /*recuperation des choix utilisateur pour le joueur, terrain et le prix*/
    *joueur = choix_joueur(plateau,joueur_courant);
    *terrain = choix_proprietes(plateau, *joueur);
    if(*terrain ==0){
        *validation = -1;
        return;
    }
    *prix = selection_prix(plateau,joueur_courant);
    
    /*denerière fenetre de recapitulatif et demande de confirmation*/
    *validation = confirmation_proposition(plateau,*joueur,*terrain,*prix);
}

/*fct qui permets de choisir un joueur different du joueur courant*/
int choix_joueur(PLATEAU *plateau, int joueur_courant){
    int retour;
    /* faire cette fonction + choix achat laison et si joueur ruiné gogogogogogogooood*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *joueur[3];
    
    SDL_Rect p_joueur[3];
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(450, 255, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Choisissez un joueur", NULL);
    
        /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*initialisation du texte*/
    int nb_joueur=0,i;
    for(i=0; i<=3;i++){
        if(i!=joueur_courant && plateau->present[i]==1){
            joueur[nb_joueur]= TTF_RenderText_Blended(police,plateau->joueurs[i]->nom, Noire);
            nb_joueur++;
        }
    }
    
    /*initialisation position*/
    int y=50;
    i=0;
    while(i<nb_joueur){
        p_joueur[i].x=fenetre->w/2 - joueur[i]->w/2;
        p_joueur[i].y=y+i*y;
        i++;
    }
    
     /*Blitage et actualisation de l'écran*/
    i=0;
    while(i<nb_joueur){
        SDL_BlitSurface(joueur[i], NULL, fenetre, &p_joueur[i]);
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
                    if(nb_joueur>=1){ 
                        if(verification_zone(&event,p_joueur[0].x ,p_joueur[0].y,joueur[0]->w,joueur[0]->h) == 1){
                            retour = 0;  
                            init_j_lauch = SDL_FALSE;
                        }
                    }
                    if(nb_joueur>=2){ 
                        if(verification_zone(&event,p_joueur[1].x ,p_joueur[1].y,joueur[1]->w,joueur[1]->h) == 1){
                            retour = 1;  
                            init_j_lauch = SDL_FALSE;
                        }
                    }
                    if(nb_joueur>=3){ /*si il n'y a que 2 joueur le bouton 3 est inactif*/
                        if(verification_zone(&event,p_joueur[2].x ,p_joueur[2].y,joueur[2]->w,joueur[2]->h) == 1){
                            retour = 2;  
                            init_j_lauch = SDL_FALSE;
                        }
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
    for(i=0; i<nb_joueur;i++){
        if(joueur[i]!=NULL){
            SDL_FreeSurface(joueur[i]);
        }
    }
    SDL_Quit();
    return identification_numero_joueur(retour,joueur_courant,plateau);
}

/*listing et selection d'une terrain apartenant au joueur "joueur_choisie"*/
/*returne le numero du terrain 1->40, 0 indique pas de terrain => confirmation =-1*/
int choix_proprietes(PLATEAU *plateau, int joueur_choisie){
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
    
    creation_couleur(Couleur_t,0, 128, 64, 0);       /*marron*/
    creation_couleur(Couleur_t,1, 0, 255, 255);     /*cyan*/
    creation_couleur(Couleur_t,2, 255, 0, 255);     /*magenta*/
    creation_couleur(Couleur_t,3, 255, 128, 0);    /*orange*/
    creation_couleur(Couleur_t,4, 255, 0, 0);       /*rouge*/
    creation_couleur(Couleur_t,5, 255, 255, 0);    /*jaune*/
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
				default:
					break;
			}
		}
    }
    i=0;
    while(i<nb_terrain){
        if(terrain[i]!=NULL) {
            SDL_FreeSurface(terrain[i]);
        }
        i++;
    }
    SDL_Quit();
    return retour;
}

/*fct qui renvoie le prix indiquer*/
int selection_prix(PLATEAU *plateau, int joueur_courant){
    char prix[20];
    strcpy(prix,"");
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *zone_prix=NULL, *texte_prix=NULL, *texte=NULL, *solde=NULL;
    SDL_Surface *bouton=NULL, *t_valider=NULL;
    
    SDL_Rect p_zone_prix, p_texte, p_texte_prix, p_b_v, p_t_v, p_t_s;
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(525, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Proposer un prix pour le terrain", NULL);
    
    /*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Blanc = {255,255,255};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*Création du bouton*/
    bouton = SDL_LoadBMP(buton);
    
    /*supression fond image boutton*/
    SDL_SetColorKey(bouton,SDL_SRCCOLORKEY,SDL_MapRGB(bouton->format,255,255,255));
    
    /*ajout texte bouton*/
    t_valider = TTF_RenderText_Blended(police,"Valider", Blanc);
    
    /*Initialisation de la position du bouton et du texte*/
    p_b_v.x= fenetre->w-(bouton->w+25);
    p_b_v.y= fenetre->h-(bouton->h+25);
    
    p_t_v.x= p_b_v.x+bouton->w/2-t_valider->w/2;
    p_t_v.y= p_b_v.y+bouton->h/2-t_valider->h/2;
    
    /*initialisation du texte*/
    char tempory_string[60];
    texte = TTF_RenderText_Blended(police,"A quelle prix voudriez vous acheter ce terrain ?", Noire);
    sprintf(tempory_string,"solde dispo : %d pp",compte_joueur(joueur_courant,plateau));
    solde=TTF_RenderText_Blended(police,tempory_string, Noire);
    
    /*Positionement du texte*/
    p_texte.x= 10;
    p_texte.y= 10;
    
    /*initialisation image*/
    zone_prix = SDL_LoadBMP(fond_pseudo);
    texte_prix = TTF_RenderText_Blended(police,"0", Noire);
     
    /*initialisation position*/
    p_zone_prix.x=fenetre->w/2-zone_prix->w/2;
    p_zone_prix.y=75;
    
    p_texte_prix.x= p_zone_prix.x+10;
    p_texte_prix.y= p_zone_prix.y+10;
    
    p_t_s.x=fenetre->w/2-zone_prix->w/2;
    p_t_s.y=p_zone_prix.y-solde->h-10;
    
    /*Blitage et actualisation de l'écran*/
    SDL_BlitSurface(texte, NULL, fenetre, &p_texte); 
    
    SDL_BlitSurface(zone_prix, NULL, fenetre, &p_zone_prix);   
    SDL_BlitSurface(texte_prix, NULL, fenetre, &p_texte_prix);   
    SDL_BlitSurface(solde, NULL, fenetre, &p_t_s);   
      
    SDL_BlitSurface(bouton, NULL, fenetre, &p_b_v);   
    SDL_BlitSurface(t_valider, NULL, fenetre, &p_t_v);   
    SDL_Flip(fenetre);
    
    /*boucle programme*/
    SDL_bool init_j_lauch = SDL_TRUE;
    
    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    if(verification_zone(&event,p_zone_prix.x ,p_zone_prix.y,zone_prix->w,zone_prix->h) == 1){
                         zone_prix = SDL_LoadBMP(fond_pseudo_s);           
                    }
                    else{
                        zone_prix = SDL_LoadBMP(fond_pseudo);
                        if(verification_zone(&event,p_b_v.x ,p_b_v.y,bouton->w,bouton->h) == 1){
                            init_j_lauch = SDL_FALSE;          
                        }    
                    }    
                    break;
                case SDL_KEYDOWN:
					modification_prix(event,prix);/*recuperation du texte Maj ou non, num , ? si touche suppr*/
                    texte_prix = TTF_RenderText_Blended(police,prix, Noire);
					break;	
				default:
					break;
			}
		}
        SDL_BlitSurface(texte, NULL, fenetre, &p_texte); 
    
        SDL_BlitSurface(zone_prix, NULL, fenetre, &p_zone_prix);   
        SDL_BlitSurface(texte_prix, NULL, fenetre, &p_texte_prix); 
        SDL_BlitSurface(solde, NULL, fenetre, &p_t_s); 
      
        SDL_BlitSurface(bouton, NULL, fenetre, &p_b_v);   
        SDL_BlitSurface(t_valider, NULL, fenetre, &p_t_v);   
        SDL_Flip(fenetre);
    }

    SDL_FreeSurface(texte);
    SDL_FreeSurface(zone_prix);
    SDL_FreeSurface(texte_prix);
    SDL_FreeSurface(solde);
    SDL_FreeSurface(bouton);
    SDL_FreeSurface(t_valider);
    
    SDL_Quit();
    if(strlen(prix)==0){
        strcpy(prix,"0");
    }
    return atoi(prix);
}

/*fct qui demande confirmatuon la proposition pour l'achat d'un terraint T, appartenant au joueur et a tel prix*/
/*1 confirmation -1 sinon*/
int confirmation_proposition(PLATEAU *plateau, int joueur, int terrain, int prix){
    int retour;
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *texte_terrain=NULL, *texte_prix=NULL, *texte_joueur=NULL, *texte=NULL;
    SDL_Surface *bouton_v=NULL, *t_valider=NULL;
    SDL_Surface *bouton_r=NULL, *t_refuser=NULL;
    
    SDL_Rect p_t_t, p_t_p, p_t_j, p_t, p_t_v, p_t_r;
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

    sprintf(tempory_string, "Joueur : %s", plateau->joueurs[joueur]->nom);
    texte_joueur = TTF_RenderText_Blended(police,tempory_string, Noire);
    
    sprintf(tempory_string, "Terrain : %s", c->nom);
    texte_terrain = TTF_RenderText_Blended(police,tempory_string, Noire);

    sprintf(tempory_string, "Prix : %d pp", prix);
    texte_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
    
    /*initialisation du texte*/
    texte = TTF_RenderText_Blended(police,"Recapitulatif de la proposition : ", Noire);
    
    /*Positionement des textes*/
    p_t.x= 10;
    p_t.y= 10;
    
    p_t_j.x = 50;
    p_t_j.y = p_t.y +30;
    
    p_t_t.x = 50;
    p_t_t.y = p_t_j.y +25;
    
    p_t_p.x = 50;
    p_t_p.y = p_t_t.y +25;
    
    /*Blitage et actualisation de l'écran*/    
    SDL_BlitSurface(texte, NULL, fenetre, &p_t); 
    SDL_BlitSurface(texte_terrain, NULL, fenetre, &p_t_t); 
    SDL_BlitSurface(texte_prix, NULL, fenetre, &p_t_p); 
    SDL_BlitSurface(texte_joueur, NULL, fenetre, &p_t_j); 
      
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
    SDL_FreeSurface(texte_joueur);
    SDL_FreeSurface(bouton_v);
    SDL_FreeSurface(bouton_r);
    SDL_FreeSurface(t_valider);
    SDL_FreeSurface(t_refuser);
    

    return retour;
    
    
    
}

/********************************/
/*fct proposition achat maison*/
/********************************/

int achat_maison(PLATEAU *plateau,int joueur_courant,int *terrain){
    int i;
    *terrain = choix_proprietes_maison_achat(plateau, joueur_courant);
    if(*terrain ==0){
        return -1;
    }
   
    CASE *c;
    c=plateau->case_depart;
    for(i=1;i<*terrain;i++){
        c=c->suivante; 
    }
    
    
   return analyse_achat_maison(*c->terrain,plateau,joueur_courant);
}

/*affiche achat maison ou hotel avec prix, -1 si annuler 1 sinon*/
int analyse_achat_maison(TERRAIN terrain, PLATEAU *plateau,int joueur_courant){
	int retour;
	int nb_maison;
	int prix;
	
	char texte[15];
    /*initialisation sdl*/
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
     /*initialisation des surface et rect*/
    SDL_Surface *fenetre = NULL;
    SDL_Surface *t_nb_maison=NULL, *t_hotel=NULL, *t_prix=NULL, *solde=NULL;
    SDL_Surface *bouton_v=NULL, *t_valider=NULL;
    SDL_Surface *bouton_a=NULL, *t_annuler=NULL;
    
    SDL_Rect p_t_nb_m, p_t_h, p_t_p, p_t_v, p_t_a, p_t_s;
    SDL_Rect p_b_a, p_b_v;
    
     /*Creation de la fenetre*/
    fenetre = SDL_SetVideoMode(625, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 213, 208, 134)); /*texture écran*/
    
    SDL_WM_SetCaption("Achat de maison", NULL);
    
	/*Creation de couleur*/
    SDL_Color Noire = {0,0,0};
    SDL_Color Blanc = {255,255,255};
    
    /*initialisation texte*/
    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    /*Création du bouton*/
    bouton_v = SDL_LoadBMP(buton);
    bouton_a = SDL_LoadBMP(buton);
	
	/*supression fond image boutton*/
    SDL_SetColorKey(bouton_v,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_v->format,255,255,255));
    SDL_SetColorKey(bouton_a,SDL_SRCCOLORKEY,SDL_MapRGB(bouton_a->format,255,255,255));
	
	/*récuperation des information*/
	nb_maison = terrain.nb_maison;
	prix= terrain.prix_batiment;
	
	if(nb_maison <4)
		strcpy(texte, "Maison $$");
	else if(nb_maison ==5)
		strcpy(texte,"NON");
    else strcpy(texte,"HOTEL $$");

    /*ajout texte bouton*/
    t_valider = TTF_RenderText_Blended(police,texte, Blanc);
    t_annuler = TTF_RenderText_Blended(police,"Refuser", Blanc);
    
    /*Initialisation de la position du bouton et du texte bouton*/
    p_b_v.x= fenetre->w-(bouton_v->w+25);
    p_b_v.y= fenetre->h-(bouton_v->h+25);
    
    p_b_a.x= 10/*(bouton_r->w+50) - p_b_v.x*/ ;
    p_b_a.y= p_b_v.y;
    
    p_t_v.x= p_b_v.x+bouton_v->w/2-t_valider->w/2;
    p_t_v.y= p_b_v.y+bouton_v->h/2-t_valider->h/2;
    
    p_t_a.x= p_b_a.x+bouton_a->w/2-t_annuler->w/2;
    p_t_a.y= p_b_a.y+bouton_a->h/2-t_annuler->h/2;
    
    /*recuperation du solde, terrain , joueur et prix*/
    char tempory_string[60];
    char tempory_string2[12];
    sprintf(tempory_string,"solde dispo : %d pp",compte_joueur(joueur_courant,plateau));
    solde=TTF_RenderText_Blended(police,tempory_string, Noire);
    
	if(nb_maison==5){
		strcpy(tempory_string2,"oui"); 	
        sprintf(tempory_string, "Nombre de Maison : %d", 4);
	}
	else {
		strcpy(tempory_string2,"non"); 
        sprintf(tempory_string, "Nombre de Maison : %d", nb_maison);
    }
    t_nb_maison = TTF_RenderText_Blended(police,tempory_string, Noire);
	
    sprintf(tempory_string, "Hotel : %s", tempory_string2);
    t_hotel = TTF_RenderText_Blended(police,tempory_string, Noire);
	
	if(nb_maison == 4){
		strcpy(tempory_string2,"un hotel"); 	
	}
	else if(nb_maison < 4)
		strcpy(tempory_string2,"une maison"); 
	
	if(nb_maison != 5){
    	sprintf(tempory_string, "Voulez vous acheter %s pour %d pp ?",tempory_string2, prix);
    	t_prix = TTF_RenderText_Blended(police,tempory_string, Noire);
	}
	else
		t_prix = TTF_RenderText_Blended(police,"Nouvel achat impossible", Noire);
    
    /*Positionement des textes*/
    p_t_nb_m.x = 50;
    p_t_nb_m.y = 20;
    
    p_t_h.x = 50;
    p_t_h.y = p_t_nb_m.y +25;
    
    p_t_p.x = 50;
    p_t_p.y = p_t_h.y +25;
    
    p_t_s.x=50;
    p_t_s.y =p_t_p.y+25;
    
    /*Blitage et actualisation de l'écran*/    
    SDL_BlitSurface(t_nb_maison, NULL, fenetre, &p_t_nb_m); 
    SDL_BlitSurface(t_hotel, NULL, fenetre, &p_t_h); 
    SDL_BlitSurface(t_prix, NULL, fenetre, &p_t_p); 
    SDL_BlitSurface(solde, NULL, fenetre, &p_t_s);     
      
    SDL_BlitSurface(bouton_v, NULL, fenetre, &p_b_v);   
    SDL_BlitSurface(t_valider, NULL, fenetre, &p_t_v);
    
    SDL_BlitSurface(bouton_a, NULL, fenetre, &p_b_a);   
    SDL_BlitSurface(t_annuler, NULL, fenetre, &p_t_a); 
    SDL_Flip(fenetre);
    
    /*boucle programme*/
    SDL_bool init_j_lauch = SDL_TRUE;

    while(init_j_lauch){
		SDL_Event event;
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
                    if(verification_zone(&event,p_b_v.x ,p_b_v.y,bouton_v->w,bouton_v->h) == 1 && nb_maison!=5){
                        retour = 1;   
                        init_j_lauch = SDL_FALSE;
                    }
                    else if(verification_zone(&event,p_b_a.x ,p_b_a.y,bouton_a->w,bouton_a->h) == 1){
                        retour = -1;
                        init_j_lauch = SDL_FALSE;
                    }
                    break;	
				default:
					break;
			}
		}
    }

    SDL_FreeSurface(t_nb_maison);
    SDL_FreeSurface(t_hotel);
    SDL_FreeSurface(t_prix);
    SDL_FreeSurface(solde);

    SDL_FreeSurface(bouton_v);
    SDL_FreeSurface(bouton_a);
    SDL_FreeSurface(t_valider);
    SDL_FreeSurface(t_annuler);
    

    return retour;
}

int choix_proprietes_maison_achat(PLATEAU *plateau, int joueur_choisie){
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
    
    creation_couleur(Couleur_t,0, 128, 64, 0);       /*marron*/
    creation_couleur(Couleur_t,1, 0, 255, 255);     /*cyan*/
    creation_couleur(Couleur_t,2, 255, 0, 255);     /*magenta*/
    creation_couleur(Couleur_t,3, 255, 128, 0);    /*orange*/
    creation_couleur(Couleur_t,4, 255, 0, 0);       /*rouge*/
    creation_couleur(Couleur_t,5, 255, 255, 0);    /*jaune*/
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
        if(c->terrain!=NULL && c->terrain->proprietaire==joueur_choisie && c->terrain->nb_maison>=0 && 
           plateau->joueurs[joueur_choisie]->terrains.terr_complet[type_terrain(nb_terrain+2,plateau)]==1 && type_terrain(nb_terrain+2,plateau)!=GARES && type_terrain(nb_terrain+2,plateau)!=COMPAGNIES){
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
        if(terrain[i]!=NULL) {
            SDL_FreeSurface(terrain[i]);
        }
        i++;
    }
    SDL_Quit();
    return retour;
}

/****************/
/*fct utilitaire*/
/****************/

/*fct qui retourne le numero du joueur en fct du bouton slectioner 0->3*/
int identification_numero_joueur(int val_retour, int joueur_courant, PLATEAU *plateau){
    int retour,i;
    switch(joueur_courant){
        case 0:
            retour= val_retour+1;
            break;
        case 1:
            if(val_retour>=1)
                retour= val_retour+1;
            else
                retour= val_retour;
            break;
        case 2:
            if(val_retour>=2)
                retour= val_retour+1;
            else
                retour= val_retour;
            break;
        case 3:
            retour= val_retour;
            break;
        default:
            return -1;
			break;
    }
    for (i=0;i<=3;i++){
        if (plateau->present[i]==0 && i<=retour) retour++;   
    }
    return retour;
}

/*fct qui modifie la chaine de caractère prix a chaque ajout de chiffre(clavier)*/
void modification_prix(SDL_Event event,char *prix){
	char c = recuperation_chiffre(event);
    if(c == '?'){
		int i = strlen(prix);
        if(i>0)
		   prix[i-1]='\0';
	}
	else{
        if(strlen(prix)<19){
            char temp[2];
            temp[0]=c;
            temp[1]='\0';
            strcat(prix,temp);
        }
	}
}









































