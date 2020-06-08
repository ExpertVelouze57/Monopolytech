#include "choix_prison.h"


/*renvoie (0) Payer, (1)carte sortie prison (2)lancer des*/
int choix_prison(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    int retour;
    
    SDL_Surface *ecran = NULL, *boutton1 = NULL, *texte1 = NULL, *boutton2 =NULL, *boutton3 = NULL, *texte2 = NULL, *texte3 = NULL;
    SDL_Rect positionbouton1, positionbouton2, positionbouton3, p_texte1, p_texte2, p_texte3;
    
    ecran = SDL_SetVideoMode(400, 200, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 213, 208, 134));
	
    SDL_WM_SetCaption("Choix prison", NULL);

    TTF_Font *police = NULL;
    police = TTF_OpenFont(POLICE, 24);
    
    SDL_Color Noire = {0,0,0};
    
    /*initialisation du texte des bouton*/
    texte1 = TTF_RenderText_Blended(police,"Payer", Noire);
    texte2 = TTF_RenderText_Blended(police,"Cartes sortie prison", Noire);
    texte3 = TTF_RenderText_Blended(police,"Lancer Des", Noire);
    
    /*initialisation des bouton*/
    boutton1 = SDL_CreateRGBSurface(SDL_HWSURFACE, texte1->w+10,texte1->h+10,32,0,0,0,0);
    SDL_FillRect(boutton1,NULL,SDL_MapRGB(boutton1->format,239,243,73));
    
    boutton2 = SDL_CreateRGBSurface(SDL_HWSURFACE, texte2->w+10,texte2->h+10,32,0,0,0,0);
    SDL_FillRect(boutton2,NULL,SDL_MapRGB(boutton2->format,239,243,73));
    
    boutton3 = SDL_CreateRGBSurface(SDL_HWSURFACE, texte3->w+10,texte3->h+10,32,0,0,0,0);
    SDL_FillRect(boutton3,NULL,SDL_MapRGB(boutton3->format,239,243,73));
    
    /*position bouton*/
    positionbouton1.x = ecran->w/2 - boutton1->w/2;
    positionbouton1.y =20;
    
    positionbouton2.x = ecran->w/2 - boutton2->w/2;
    positionbouton2.y =positionbouton1.y + boutton1->h + 30;
    
    positionbouton3.x = ecran->w/2 - boutton3->w/2;
    positionbouton3.y =positionbouton2.y + boutton2->h + 30;
  
    /*position texte*/
    p_texte1.x = positionbouton1.x+boutton1->w/2-texte1->w/2;
    p_texte1.y = positionbouton1.y+boutton1->h/2-texte1->h/2;
   
    p_texte2.x = positionbouton2.x+boutton2->w/2-texte2->w/2;
    p_texte2.y = positionbouton2.y+boutton2->h/2-texte2->h/2;

    p_texte3.x = positionbouton3.x+boutton3->w/2-texte3->w/2;
    p_texte3.y = positionbouton3.y+boutton3->h/2-texte3->h/2;

    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(boutton1, NULL, ecran, &positionbouton1);
    SDL_BlitSurface(texte1, NULL, ecran, &p_texte1);
    
    SDL_BlitSurface(boutton2, NULL, ecran, &positionbouton2);
    SDL_BlitSurface(texte2, NULL, ecran, &p_texte2);
    
    SDL_BlitSurface(boutton3, NULL, ecran, &positionbouton3);
    SDL_BlitSurface(texte3, NULL, ecran, &p_texte3);
    
    SDL_Flip(ecran);
    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,positionbouton1.x ,positionbouton1.y ,boutton1->w,boutton1->h) == 1){
                        retour = 0;  
                        init_j_lauch = SDL_FALSE;
                    }
                    if(verification_zone(&event,positionbouton2.x ,positionbouton2.y ,boutton2->w,boutton2->h) == 1){
                        retour = 1;  
                        init_j_lauch = SDL_FALSE;
                    }
                    if(verification_zone(&event,positionbouton3.x ,positionbouton3.y ,boutton3->w,boutton3->h) == 1){
                        retour = 2;  
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				default:
					break;
			}
		}
    }
    
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(boutton1); /* On libère la surface */
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(boutton2); /* On libère la surface */
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(boutton3); /* On libère la surface */
    SDL_Quit();

    return retour;
}

