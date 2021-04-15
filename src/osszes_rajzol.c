#include "osszes_rajzol.h"

extern int W, H;
extern int EX, EY;
extern bool beallit;
extern Betutipus* betutipus;

static int grad_color(int color, int i){
    return color - i / realtoint(W / color);
}

static void draw_gradient(SDL_Renderer *renderer){
    for (int i = 0; i < W; i++) {
        lineRGBA(renderer, 0, i, W, i, 0, grad_color(120, i), grad_color(255, i), 100);
    }
}
SDL_Color sotet = {22, 22, 22};

/*
 * Egyben az összes többi rajzolós fv és így csak egyszer kell meghívni
 * */
void rajzolas(SDL_Renderer* renderer, Szim* const szim, Bevstring const bevstring, int const melyik, Error const hiba, bool stop){
    //Rajzolás előtti felkészülés
    SDL_SetRenderDrawColor(renderer,22,22,22,255);
    SDL_RenderClear(renderer);
    //***************************

    //Háttérszín kirajzolása
    draw_gradient(renderer);
    //Felső sáv kirajzolása
    boxRGBA(renderer, 0, 0, W, H * SAV_SZEL, 200, 200, 200, 255);
    //felső sáv szöveg kiírása
    kiir(renderer, betutipus[0].tipus, sotet, "Vírusszimulátor", W/2 - 80, 8);
    //
    if (stop)
        kiir(renderer, betutipus[1].tipus, sotet, "SZÜNETEL", 10, 8);
    //X gomb
    exit_gomb(renderer, katt(EX, EY, W - 25, W - 5, 0, H * SAV_SZEL));
    //Szimulációk állapotától függő dinamikus kirajzolás
    for (int i = 0; i < SZIMSZAM; ++i) {
        if (szim[i].all){
            keret(renderer, szim, i);
            szim_rajzol(renderer, szim, i);
            graf_alap_rajzol(renderer, szim, i);
            valt_gomb(renderer, szim, i);
            ujraindit_gomb(renderer, szim, i);
            torol_gomb(renderer, szim, i);
            szim_info(renderer, szim, i);
            if (szim[i].graf->utso->fert == 0)
                export_svg(renderer, szim, i);
        }
        keret(renderer, szim, i);
        hozzaad_gomb(renderer, szim, i);
    }
    if (beallit) {
        beallitas(renderer, bevstring, melyik, hiba);
    }
    SDL_RenderPresent(renderer);
}