#ifndef CHOIX_PRISON_H
#define CHOIX_PRISON_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#include "aide_graphique.h"

#define POLICE "police/arial/arial_narrow_7.ttf"

/*renvoie (0) Payer, (1)carte sortie prison (2)lancer des*/
int choix_prison();

#endif