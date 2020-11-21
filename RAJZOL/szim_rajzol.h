#ifndef NHF_SZIM_RAJZOL_H
#define NHF_SZIM_RAJZOL_H

#include "../def.h"
#include "../globalis_fvek.h"

void szim_rajzol(SDL_Renderer *renderer, Szim* const szimulacio, int i);
void keret(SDL_Renderer *renderer, Szim* const szim, int i);

#endif