#include "dinamikus_elemek_rajzol.h"

extern int W, H;
extern int EX, EY;
extern bool beallit;
extern Betutipus* betutipus;
extern Bevitel bevitel;

void exit_gomb(SDL_Renderer* renderer, bool hower){
    if (hower) {
        SDL_Color piros_hal = {160, 0, 0, 50};
        kiir(renderer, betutipus[0].tipus, piros_hal, "X", W - 25, 4);
    }
    else {
        SDL_Color piros = {160, 0, 0, 255};
        kiir(renderer, betutipus[0].tipus, piros, "X", W - 25, 4);
    }
}

static void ertek_stringbe_masol(char* ide, char const ellenorzo[]){
    if (atoi(ellenorzo) != 0)
        sprintf(ide, "%d", atoi(ellenorzo));
    else
        sprintf(ide, "-");
}

void beallitas(SDL_Renderer* renderer, Bevstring const bevstring, int const melyik){
    SDL_Color vilagos = {200, 200, 200, 255};
    SDL_Color vilagos_hal = {200, 200, 200, 150};
    int x1 = W / 6 * 2;
    int x2 = W / 6 * 4;
    int y1 = 200;
    int y2 = H - y1;
    //Háttér sötétítése
    boxRGBA(renderer, 0, H * SAV_SZEL, W, H, 50, 50, 50, 150);
    //Doboz amiben minden beállítás van
    boxRGBA(renderer, x1, y1, x2, y2, 50, 50, 50, 230);

    //Beviteli mezők
    boxRGBA(renderer, W / 2 + 130, y1 + 195, x2 - 90, y1 + 230, 40, 40, 40, 220);
    boxRGBA(renderer, W / 2 + 130, y1 + 270, x2 - 90, y1 + 305, 40, 40, 40, 220);
    boxRGBA(renderer, W / 2 + 130, y1 + 345, x2 - 90, y1 + 380, 40, 40, 40, 220);
    boxRGBA(renderer, W / 2 + 130, y1 + 420, x2 - 90, y1 + 455, 40, 40, 40, 220);

    //Beviteli mezők "dimenziójának kiírása"
    kiir(renderer, betutipus[0].tipus, vilagos, "egyed", W / 2 + 240, y1 + 202);
    kiir(renderer, betutipus[0].tipus, vilagos, "egység", W / 2 + 240, y1 + 277);
    kiir(renderer, betutipus[0].tipus, vilagos, "%", W / 2 + 240, y1 + 352);
    kiir(renderer, betutipus[0].tipus, vilagos, "egység", W / 2 + 240, y1 + 422);

    //Beállítás és szimuláció kiírása
    kiir(renderer, betutipus[2].tipus, vilagos, "Beállítások", W / 2 - 120, y1 + 10);
    char szimul[16];
    sprintf(szimul, "%d. szimuláció", melyik + 1);
    kiir(renderer, betutipus[0].tipus, vilagos, szimul, W / 2 - 70, y1 + 60);

    //Beviteli infók kiírása
    kiir(renderer, betutipus[0].tipus, vilagos, "Népesség mérete:", x1 + 20, y1 + 200);
    kiir(renderer, betutipus[0].tipus, vilagos, "Vírus terjedési sugara:", x1 + 20, y1 + 275);
    kiir(renderer, betutipus[0].tipus, vilagos, "Fertözési százalék(%):", x1 + 20, y1 + 350);
    kiir(renderer, betutipus[0].tipus, vilagos, "Gyógyulási idö:", x1 + 20, y1 + 420);

    //Aktív beviteli mező kirajzolása
    switch (bevitel) {
        case Nepesseg:
            rectangleRGBA(renderer, W / 2 + 130, y1 + 195, x2 - 90, y1 + 230, 220, 220, 220, 220);
            break;
        case Sugar:
            rectangleRGBA(renderer, W / 2 + 130, y1 + 270, x2 - 90, y1 + 305, 220, 220, 220, 220);
            break;
        case Szazalek:
            rectangleRGBA(renderer, W / 2 + 130, y1 + 345, x2 - 90, y1 + 380, 220, 220, 220, 220);
            break;
        case Ido:
            rectangleRGBA(renderer, W / 2 + 130, y1 + 420, x2 - 90, y1 + 455, 220, 220, 220, 220);
            break;
    }

    //Bevitt értékek kiírása
    char nep[4 + 1], sug[2 + 1], szaz[3 + 1], ido[3 + 1];
    ertek_stringbe_masol(nep, bevstring.nep);
    ertek_stringbe_masol(sug, bevstring.sug);
    ertek_stringbe_masol(szaz, bevstring.szaz);
    ertek_stringbe_masol(ido, bevstring.ido);
    kiir(renderer, betutipus[0].tipus, vilagos, nep, W / 2 + 140, y1 + 202);
    kiir(renderer, betutipus[0].tipus, vilagos, sug, W / 2 + 140, y1 + 277);
    kiir(renderer, betutipus[0].tipus, vilagos, szaz, W / 2 + 140, y1 + 352);
    kiir(renderer, betutipus[0].tipus, vilagos, ido, W / 2 + 140, y1 + 427);

    //indítás gomb
    if (katt(EX, EY, x2 - 20 - 100, x2 - 20, y2 - 60, y2 - 20)){
        boxRGBA(renderer, x2 - 20, y2 - 60, x2 - 20 - 100, y2 - 20, 40, 40, 40, 150);
        kiir(renderer, betutipus[1].tipus, vilagos_hal, "MÉGSE", x2 - 100, y2 - 50);
    } else{
        boxRGBA(renderer, x2 - 20, y2 - 60, x2 - 20 - 100, y2 - 20, 40, 40, 40, 220);
        kiir(renderer, betutipus[1].tipus, vilagos, "MÉGSE", x2 - 100, y2 - 50);
    }

    //mégse gomb
    if (katt(EX, EY, x1 + 20, x1 + 20 + 200, y2 - 60, y2 - 20)){
        boxRGBA(renderer, x1 + 20, y2 - 60, x1 + 20 + 200, y2 - 20, 40, 40, 40, 150);
        kiir(renderer, betutipus[1].tipus, vilagos_hal, "MENTÉS ÉS INDÍTÁS", x1 + 35, y2 - 50);
    } else{
        boxRGBA(renderer, x1 + 20, y2 - 60, x1 + 20 + 200, y2 - 20, 40, 40, 40, 220);
        kiir(renderer, betutipus[1].tipus, vilagos, "MENTÉS ÉS INDÍTÁS", x1 + 35, y2 - 50);
    }
}

void valt_gomb(SDL_Renderer* renderer, Szim* const szim, int i){
    SDL_Color sotet = {30, 30, 30, 255};
    SDL_Color sotet_hal = {30, 30, 30, 150};
    int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
    int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50);
    bool hower = katt(EX, EY, x,x + 100, y, y + 30);
    if(!beallit && hower){
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 150);
        kiir(renderer, betutipus[3].tipus, sotet_hal, "BEÁLLÍTÁSOK", x + 8, y + 8);
    }
    else{
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 255);
        kiir(renderer, betutipus[3].tipus, sotet, "BEÁLLÍTÁSOK", x + 8, y + 8);
    }
}

void ujraindit_gomb(SDL_Renderer* renderer, Szim* const szim, int i){
    SDL_Color sotet = {30, 30, 30, 255};
    SDL_Color sotet_hal = {30, 30, 30, 150};
    int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
    int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 50;
    bool hower = katt(EX, EY, x,x + 100, y, y + 30);
    if(!beallit && hower){
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 150);
        kiir(renderer, betutipus[1].tipus, sotet_hal, "ÚJRAINDÍT", x + 5, y + 6);
    }
    else{
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 255);
        kiir(renderer, betutipus[1].tipus, sotet, "ÚJRAINDÍT", x + 5, y + 6);
    }
}

void torol_gomb(SDL_Renderer* renderer, Szim* const szim, int i){
    SDL_Color sotet = {220, 220, 220, 255};
    SDL_Color sotet_hal = {230, 230, 230, 150};
    int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
    int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 100;
    bool hower = katt(EX, EY, x,x + 100, y, y + 30);
    if(!beallit && hower){
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 0, 0, 150);
        kiir(renderer, betutipus[1].tipus, sotet_hal, "TÖRÖL", x + 20, y + 6);
    }
    else{
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 0, 0, 255);
        kiir(renderer, betutipus[1].tipus, sotet, "TÖRÖL", x + 20, y + 6);
    }
}

void hozzaad_gomb(SDL_Renderer* renderer, Szim* const szim, int i){
    if (!szim[i].all){
        SDL_Color sotet = {30, 30, 30, 255};
        SDL_Color sotet_hal = {30, 30, 30, 150};
        int x = W / 4 - 30;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + (W * TART_SZEL) / 2 - 30;
        bool hower = katt(EX, EY, x,x + 60, y, y + 60);
        if (!beallit && hower){
            boxRGBA(renderer, x, y, x + 60, y + 60, 200, 200, 200, 150);
            kiir(renderer, betutipus[1].tipus, sotet_hal, "ÚJ", x + 20, y + 22);
        }
        else {
            boxRGBA(renderer, x, y, x + 60, y + 60, 200, 200, 200, 255);
            kiir(renderer, betutipus[1].tipus, sotet, "ÚJ", x + 20, y + 22);
        }
    }
}