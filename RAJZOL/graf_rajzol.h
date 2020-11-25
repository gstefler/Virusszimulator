#ifndef NHF_GRAF_RAJZOL_H
#define NHF_GRAF_RAJZOL_H

#include "../def.h"
#include "../globalis_fvek.h"

enum Melyik{Fert, Gyogy, X_koo};

Sint16* belerak(Grafikon* const graf, enum Melyik melyik, double const arany, int const szeleseg, double const novelo, int const x, int const y, int const y1);
void graf_alap_rajzol(SDL_Renderer * renderer, Szim* const szim, int i);

#endif
