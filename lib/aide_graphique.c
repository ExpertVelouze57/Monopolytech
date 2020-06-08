/******************************************************************************************/
/*																						  */
/*        Contenu du fichier: fonction utilisant la sdl (générique)			     		  */
/*05/05/2020																			  */
/*																						  */
/******************************************************************************************/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "aide_graphique.h"


/*fct qui remplit un tableau de SDL couleur, num = indice tableau, R,G,B valeur 0->255*/
void creation_couleur(SDL_Color *T, int num, int R, int G, int B){
    T[num].r=R;
    T[num].g=G;
    T[num].b=B;  
}

/*fct qui retourne un caratère en fct de se qui est entré au clavier (numerique uniquement*/
char recuperation_chiffre(SDL_Event event){
    char c;
	switch(event.key.keysym.sym){
		case SDLK_KP0:
        case SDLK_0:
				c='0';
				break;
        case SDLK_KP1:
        case SDLK_1:
				c='1';
				break;
		case SDLK_KP2:
        case SDLK_2:
				c='2';
				break;
		case SDLK_KP3:
        case SDLK_3:
				c='3';
				break;
		case SDLK_KP4:
        case SDLK_4:
				c='4';
				break;
		case SDLK_KP5:
        case SDLK_5:
				c='5';
				break;
		case SDLK_KP6:
        case SDLK_6:
				c='6';
				break;
        case SDLK_KP7:
        case SDLK_7:
				c='7';
				break;
		case SDLK_KP8:
        case SDLK_8:
				c='8';
				break;
		case SDLK_KP9:
        case SDLK_9:
				c='9';
				break;
        case SDLK_BACKSPACE:
				c='?';
				break;
		default:
				c='\0';
				break;
		}
    return c;
}