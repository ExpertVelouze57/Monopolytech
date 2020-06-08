/******************************************************************************************/
/*																						  */
/*        Contenu du fichier: fonction utilisant la sdl (générique)			     		  */
/*05/05/2020																			  */
/*																						  */
/******************************************************************************************/
#ifndef AIDE_GRAPHIQUE
#define AIDE_GRAPHIQUE

#include "init_joueur.h"


/*fct qui remplie un tableau de SDL couleur, num = indice tableau, R,G,B valeur 0->255*/
void creation_couleur(SDL_Color *T, int num, int R, int G, int B);

/*fct qui retourne un caratère en fct de se qui est entré au clavier (numerique uniquement*/
char recuperation_chiffre(SDL_Event event);


#endif