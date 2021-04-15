#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string.h>
#include "debugmalloc.h"

#define SZIMSZAM 3
#define TART_SZEL 0.15
#define SAV_SZEL 0.03
#define R 3

/*
Típus egy egyed állapotának meghatározásához
*/
typedef enum Allapot
{
    Fogekony, Fertozott, Gyogyult
}Allapot;

/*
Típus egy egyed helyzetének(x, y) és sebességének(vx, vy) meghatározásához
*/
typedef struct Hely
{
    double x, y;
    double vx, vy;
}Hely;

/*
Típus a népesség beli egyedekhez
Tartalmazza az egyed állapotát, helyét és megbetegdésének idejét
*/
typedef struct Egyed
{
    Hely hely;
    Allapot allapot;
    int miota;
    int mennyit;
}Egyed;

/*
Típus az adott szimuláció vírusának a tulajdonságainak a tárolására
*/
typedef struct Virus
{
    int r;  //mekkora körben fertőz
    double p;   //időegységenként mekkor eséllyel fertőz az r en belül
    int recover; //mennyi idő után gyógyulnak meg belőle mp-ben
}Virus;

/*
Láncolt lista típus a grafikon értékeinek a tárolásához
*/
typedef struct GrafLista
{
    int fert, gogyult;
    struct GrafLista* kov;
}GrafLista;

/*
Típus amiben eltároljuk az első és az utolosó listaelemre mutató pointert(megkönnyíti a végére szúrást)
És a grafkion méretét ami egyébkén az eddig eltelt idő mp-ben
Így nem kell minden egyes grafikonműveletnél kiszámolni a grafikon méretét
*/
typedef struct Grafikon
{
    int meret;
    GrafLista* elso;
    GrafLista* utso;
}Grafikon;

/*
Szimulációkat leíró típus, benne van minden infó egy adott szimulációrol
*/
typedef struct Szim {
    int nepmeret; //népesség mérete
    Egyed *nep; //népesség egyedeinek tömbje
    Virus virus; //vírusparaméterei
    Grafikon *graf; //grafikon eleminek láncolt listája
    bool all; //alvó állapot
}Szim;

/*
 * Struktúra a betűtípusnak
 */
typedef struct Betutipus{
    TTF_Font* tipus;
    int meret; //betű mérete
}Betutipus;

//típús amiben a beviteli értékek vannak
typedef struct Bevstring{
    char nep[4 + 1], sug[2 + 1], szaz[3 + 1], ido[3 + 1];
}Bevstring;

//bevitel melyik állapotában vagyunk éppen
typedef enum Bevitel {
    Semmi, Nepesseg, Sugar, Szazalek, Ido, Hiba
} Bevitel;

//típus a beviteli hibának
typedef struct Error{
    Bevitel hibak[4];
    int hibak_szama;
}Error;

#endif