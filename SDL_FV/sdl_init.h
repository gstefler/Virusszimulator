#ifndef SDL_INIT_H
#define SDL_INIT_H

#include "../def.h"

void init_TTF(Betutipus *pbetutipus, int db);
void init_SDL(void);
void create(SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);

#endif