#include "sdl_init.h"

extern int W, H;

void init_TTF(Betutipus *pbetutipus, int db){
    if (TTF_Init() != 0){
        SDL_Log("TTF inicializálási hiba! %s\n", TTF_GetError());
        exit(1);
    }
    for (int i = 0; i < db; ++i) {
        pbetutipus[i].tipus = TTF_OpenFont("font.ttf", pbetutipus[i].meret);
        if (!pbetutipus[i].tipus) {
            SDL_Log("Nem sikerult megnyitni a betűtípust! %s\n", TTF_GetError());
            exit(1);
        }
    }
}

/*
Az SDL inicializálása és a képernyő méretének lekérése,
annak a W és a H változóba írása
*/
void init_SDL(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Nem inditható az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        exit(1);
    }
    W = dm.w;
    H = dm.h;
}

/*
Ablak és render létrehozása, teljes képernyős módba rakás
*/
void create(SDL_Window **pwindow, SDL_Renderer **prenderer){
    SDL_Window *window = SDL_CreateWindow("Vírus szimulátor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    if (window == NULL) {
        SDL_Log("Nem hozható letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Nem hozható letre a megjelenitő: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    *pwindow = window;
    *prenderer = renderer;
}

/*
Időzitő létrehozása
*/
Uint32 idozit(Uint32 ms, void *param){
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}