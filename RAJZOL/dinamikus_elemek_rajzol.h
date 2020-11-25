#ifndef NHF_DINAMIKUS_ELEMEK_RAJZOL_H
#define NHF_DINAMIKUS_ELEMEK_RAJZOL_H

#include "../def.h"
#include "../globalis_fvek.h"

void exit_gomb(SDL_Renderer* renderer, bool hower);
void beallitas(SDL_Renderer* renderer, Bevstring const bevstring, int const melyik);
void valt_gomb(SDL_Renderer* renderer, Szim* const szim, int i);
void hozzaad_gomb(SDL_Renderer* renderer, Szim* const szim, int i);
void ujraindit_gomb(SDL_Renderer* renderer, Szim* const szim, int i);
void torol_gomb(SDL_Renderer* renderer, Szim* const szim, int i);
void export_svg(SDL_Renderer* renderer, Szim* const szim, int i);
void szim_info(SDL_Renderer* renderer, Szim* const szim, int i);

#endif