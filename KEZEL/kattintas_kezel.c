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
            szim[i].rmax = 0;
            szim[i].elozo = 0;
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

void megse(void){
    int x2 = W / 6 * 4;
    int y1 = 200;
    int y2 = H - y1;
    if (beallit){
        if (katt(EX, EY, x2 - 20 - 100, x2 - 20, y2 - 60, y2 - 20)){
            beallit = false;
        }
    }
}

static Error hiba_keres(Bevstring const bevstring){
    int nep_min = 20;
    int sug_min = R + 1;
    int szaz_min = 1;
    int ido_min = 1;
    int hibak_szama = 0;

    Error hiba;

    if (bevstring.nep[0] == '\0' || atoi(bevstring.nep) < nep_min)
        hiba.hibak[hibak_szama++] = Nepesseg;
    if (bevstring.sug[0] == '\0' || atoi(bevstring.sug) < sug_min)
        hiba.hibak[hibak_szama++] = Sugar;
    if (bevstring.szaz[0] == '\0' || atoi(bevstring.szaz) < szaz_min)
        hiba.hibak[hibak_szama++] = Szazalek;
    if (bevstring.ido[0] == '\0' || atoi(bevstring.ido) < ido_min)
        hiba.hibak[hibak_szama++] = Ido;
    hiba.hibak_szama = hibak_szama;
    return hiba;
}

 void inditas(Szim* szim, int melyik, Bevstring* bev, bool* stop, Error* hiba){
    if (beallit){
        int x = W / 6 * 2;
        int y = H - 200;
        *hiba = hiba_keres(*bev);
        if (katt(EX, EY, x + 20, x + 20 + 200, y - 60, y - 20) && !hiba->hibak_szama){
            szim[melyik].all = true;
            szim[melyik].nepmeret = atoi(bev->nep);
            szim[melyik].virus.r = atoi(bev->sug);
            szim[melyik].virus.p = atoi(bev->szaz) / 100.0;
            szim[melyik].virus.recover = atoi(bev->ido);
            nepvaltozat(&szim[melyik]);
            szim[melyik].rmax = 0;
            szim[melyik].elozo = 0;
            beallit = false;
            *stop = false;
            bev->nep[0] = '\0';
            bev->sug[0] = '\0';
            bev->szaz[0] = '\0';
            bev->ido[0] = '\0';
        }
        else if (katt(EX, EY, x + 20, x + 20 + 200, y - 60, y - 20) && hiba->hibak_szama)
            bevitel = Hiba;

    }
}

void svg_export_katt(Szim* const szim, int* szamlalo){
    for (int i = 0; i < SZIMSZAM; ++i) {
        int x = realtoint((W / 4 - W * TART_SZEL) / 2.0) - 50;
        int y = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50) + 150;
        if (!beallit && szim[i].all && szim[i].graf->utso->fert == 0 && katt(EX, EY, x, x + 100, y, y + 30)){
            SVG_export(szim, i, szamlalo);
        }
    }
}
