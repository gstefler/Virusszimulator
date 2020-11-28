#include "dinamikus_elemek_rajzol.h"

extern int W, H;
extern int EX, EY;
extern bool beallit;
extern Betutipus* betutipus;
extern Bevitel bevitel;

/* Jobb felül a kis X gomb
 * */
void exit_gomb(SDL_Renderer* renderer, bool hower){
    if (hower) {
        SDL_Color piros_hal = {160, 0, 0, 50};
        kiir(renderer, betutipus[0].tipus, piros_hal, "X", W - 25, 8);
    }
    else {
        SDL_Color piros = {160, 0, 0, 255};
        kiir(renderer, betutipus[0].tipus, piros, "X", W - 25, 8);
    }
}

void szim_info(SDL_Renderer* renderer, Szim* const szim, int i){
    SDL_Color szurke = {20, 20, 20, 255};
    int x1 = W / 2 + W * TART_SZEL * 2 + 150;
    int x2 = x1 + 200;
    int y1 = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 20;
    int y2 = y1 + W * TART_SZEL - 40;
    boxRGBA(renderer, x1, y1, x2, y2, 220, 220, 220, 100);
    Bevstring info;
    char r0[15];
    char r0_max[15];
    sprintf(r0, "R = %.2f", szim[i].R0);
    sprintf(r0_max, "R max = %.2f", szim[i].rmax);
    sprintf(info.nep, "%d", szim[i].nepmeret);
    sprintf(info.sug, "%d", szim[i].virus.r);
    sprintf(info.szaz, "%d", (int)(szim[i].virus.p * 100));
    sprintf(info.ido, "%d", szim[i].virus.recover);
    kiir(renderer, betutipus[1].tipus, szurke, "népesség =", x1 + 5, y1 + 8);
    kiir(renderer, betutipus[1].tipus, szurke, info.nep, x1 + 110, y1 + 9);
    kiir(renderer, betutipus[1].tipus, szurke, "terj. sugár =", x1 + 5, y1 + 40);
    kiir(renderer, betutipus[1].tipus, szurke, info.sug, x1 + 110, y1 + 41);
    kiir(renderer, betutipus[1].tipus, szurke, "fert. esély =", x1 + 5, y1 + 72);
    kiir(renderer, betutipus[1].tipus, szurke, info.szaz, x1 + 110, y1 + 73);
    kiir(renderer, betutipus[1].tipus, szurke, "%", x1 + 135, y1 + 73);
    kiir(renderer, betutipus[1].tipus, szurke, "gyogy. idö = ", x1 + 5, y1 + 104);
    kiir(renderer, betutipus[1].tipus, szurke, info.ido, x1 + 110, y1 + 105);
    kiir(renderer, betutipus[1].tipus, szurke, r0, x1 + 5, y1 + 137);
    kiir(renderer, betutipus[1].tipus, szurke, r0_max, x1 + 5, y1 + 169);
}

static void ertek_stringbe_masol(char* ide, char const ellenorzo[]){
    if (atoi(ellenorzo) != 0)
        sprintf(ide, "%d", atoi(ellenorzo));
    else
        sprintf(ide, "-");
}


void beallitas(SDL_Renderer* renderer, Bevstring const bevstring, int const melyik, Error const hiba){
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
    kiir(renderer, betutipus[0].tipus, vilagos, "Fertözési esélye(%):", x1 + 20, y1 + 350);
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
        case Hiba:
            for (int i = 0; i < hiba.hibak_szama; ++i) {
                switch (hiba.hibak[i]) {
                    case Nepesseg:
                        rectangleRGBA(renderer, W / 2 + 130, y1 + 195, x2 - 90, y1 + 230, 220, 0, 0, 220);
                        break;
                    case Sugar:
                        rectangleRGBA(renderer, W / 2 + 130, y1 + 270, x2 - 90, y1 + 305, 220, 0, 0, 220);
                        break;
                    case Szazalek:
                        rectangleRGBA(renderer, W / 2 + 130, y1 + 345, x2 - 90, y1 + 380, 220, 0, 0, 220);
                        break;
                    case Ido:
                        rectangleRGBA(renderer, W / 2 + 130, y1 + 420, x2 - 90, y1 + 455, 220, 0, 0, 220);
                        break;
                }
            }
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

void export_svg(SDL_Renderer* renderer, Szim* const szim, int i){
    SDL_Color sotet = {30, 30, 30, 255};
    SDL_Color sotet_hal = {30, 30, 30, 150};
    int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
    int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 150;
    bool hower = katt(EX, EY, x,x + 100, y, y + 30);
    if(!beallit && hower){
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 150);
        kiir(renderer, betutipus[3].tipus, sotet_hal, "EXPORT SVG", x + 10, y + 9);
    }
    else{
        boxRGBA(renderer, x, y, x + 100, y + 30, 200, 200, 200, 255);
        kiir(renderer, betutipus[3].tipus, sotet, "EXPORT SVG", x + 10, y + 9);
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