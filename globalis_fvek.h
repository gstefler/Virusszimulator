#ifndef NHF_GLOBALIS_FVEK_H
#define NHF_GLOBALIS_FVEK_H

#include "def.h"

void kiir(SDL_Renderer *renderer, TTF_Font *font, SDL_Color szin, char *szov, int x, int y);
int realtoint(double r);
bool katt(int mouse_x, int mouse_y, int x1, int x2, int y1, int y2);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);

#endif //NHF_GLOBALIS_FVEK_H
