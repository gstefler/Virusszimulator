#include "globalis_fvek.h"

/*
Kiír egy szöveget
*/
void kiir(SDL_Renderer *renderer, TTF_Font *font, SDL_Color szin, char *szov, int x, int y){
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = {0, 0, 0, 0};
    felirat = TTF_RenderUTF8_Blended(font, szov, szin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = x;
    hova.y = y;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

int realtoint(double r){
    if ((int)(10 * r) / 10 < 5)
        return (int)r;
    return ((int)r) + 1;
}

/*
 *Kattintások kezelése:
 * bemenet: egér x és y koordinataja és a 4 vizsgálandó koordináta amiben
 * megnézi hogy benne van-e
 * ha igen akkor igaz értékkel tér vissza
 */
bool katt(int mouse_x, int mouse_y, int x1, int x2, int y1, int y2){
    return (mouse_x > x1 && mouse_x < x2 && mouse_y > y1 && mouse_y < y2);
}