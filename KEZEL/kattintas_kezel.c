#include "kattintas_kezel.h"

extern int W, H;
extern int EX, EY;
extern bool beallit;
extern Bevitel bevitel;

void kilepes(bool* quit){
    *quit = katt(EX, EY, W - 25, W - 5, 0, H * SAV_SZEL);
}

void valt(Szim* const szim, bool* stop, int* melyiket){
    for (int i = 0; i < SZIMSZAM; ++i) {
        int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50);
        if (!beallit && szim[i].all &&katt(EX, EY, x,x + 100, y, y + 30)){
            *stop = true;
            beallit = true;
            *melyiket = i;
        }
    }
}

void torol(Szim* szim){
    for (int i = 0; i < SZIMSZAM; ++i) {
        int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 100;
        if (!beallit && szim[i].all && katt(EX, EY, x,x + 100, y, y + 30)){
            szim[i].all = false;
        }
    }
}

void ujraindit(Szim* szim){
    for (int i = 0; i < SZIMSZAM; ++i) {
        int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 50;
        if (!beallit && szim[i].all && katt(EX, EY, x,x + 100, y, y + 30)){
            nepvaltozat(&szim[i]);
        }
    }
}

void uj(Szim* const szim, bool* stop, int* melyik){
    for (int i = 0; i < SZIMSZAM; ++i) {
        int x = W / 4 - 30;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + (W * TART_SZEL) / 2 - 30;
        if (!beallit && !szim[i].all && katt(EX, EY, x, x + 60, y, y + 60)){
            beallit = true;
            *melyik = i;
            *stop = true;
        }
    }
}

void bevitel_valaszt(void){
    if (beallit){
        int x = W / 6 * 4;
        int y = 200;
        if (katt(EX, EY, W / 2 + 140, x - 30, y + 195, y + 230))
            bevitel = Nepesseg;
        else if (katt(EX, EY, W / 2 + 140, x - 30, y + 270, y + 305))
            bevitel = Sugar;
        else if (katt(EX, EY, W / 2 + 140, x - 30, y + 345, y + 380))
            bevitel = Szazalek;
        else if (katt(EX, EY, W / 2 + 140, x - 30, y + 420, y + 455))
            bevitel = Ido;
        else
            bevitel = Semmi;
    }
}

static bool nincs_nulla(Bevstring const bevstring){
    return (atoi(bevstring.nep) != 0 && atoi(bevstring.sug) != 0 && atoi(bevstring.szaz) != 0);
}

void inditas(Szim* szim, int melyik, Bevstring const bevstring, bool* stop){
    if (beallit){
        int x = W / 6 * 2;
        int y = H - 200;
        if (katt(EX, EY, x + 20, x + 20 + 200, y - 60, y - 20) && nincs_nulla(bevstring)){
            szim[melyik].all = true;
            szim[melyik].nepmeret = atoi(bevstring.nep);
            szim[melyik].virus.r = atoi(bevstring.sug);
            szim[melyik].virus.p = atoi(bevstring.szaz) / 100.0;
            szim[melyik].virus.recover = atoi(bevstring.ido);
            nepvaltozat(&szim[melyik]);
            beallit = false;
        }
    }
}