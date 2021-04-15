#ifndef NHF_OSSZES_RAJZOL_H
#define NHF_OSSZES_RAJZOL_H

#include "dinamikus_elemek_rajzol.h"
#include "szim_rajzol.h"
#include "graf_rajzol.h"

void rajzolas(SDL_Renderer* renderer, Szim* const szim, Bevstring const bevstring, int const melyik, Error const hiba, bool stop);

#endif
