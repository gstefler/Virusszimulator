#include "beallitas_kezel.h"

extern Bevitel bevitel;
extern Betutipus *betutipus;

static void egyel_kevesebb_masol(char* ebbe, char* const ezt){
    for (size_t i = 0; i < strlen(ezt)-1; ++i) {
        ebbe[i] = ezt[i];
    }
    ebbe[strlen(ezt)-1] = '\0';
}

void bevisz(Szim* szim, Bevstring* bevstring, Uint32 szam_be){
    //kényszerek az értékekre
    int nep_max = 2000;
    int sug_max = 50;
    int szaz_max = 99;
    int ido_max = 100;
    //***********************

    //A beállításokban az enter gomb kezelése
    if (szam_be == SDLK_RETURN){
        switch (bevitel) {
            case Nepesseg:
                bevitel = Sugar;
                break;
            case Sugar:
                bevitel = Szazalek;
                break;
            case Szazalek:
                bevitel = Ido;
                break;
            case Ido:
                bevitel = Semmi;
                break;
        }
        return;
    }

    //beviteli szám stringé alakítása
    char szam[1];
    szam[0] = szam_be;
    //*******************************

    //tesztelő bevitel, hogy ne írhassunk a kényszereknél nagyobb számot
    char* tesztelo = (char*)malloc(7 * sizeof(char));
    tesztelo[0] = '\0';

    switch (bevitel) {
        case Nepesseg:
            if (szam_be == SDLK_BACKSPACE){
                egyel_kevesebb_masol(tesztelo, bevstring->nep);
                free(bevstring->nep);
                bevstring->nep = tesztelo;
            }
            else{
                strcpy(tesztelo, bevstring->nep);
                strcat(tesztelo, szam);
                if (atoi(tesztelo) <= nep_max){
                    free(bevstring->nep);
                    bevstring->nep = tesztelo;
                }
                else {
                    bevstring->nep[0] = '\0';
                    free(tesztelo);
                }
            }
            break;
        case Sugar:
            if (szam_be == SDLK_BACKSPACE){
                egyel_kevesebb_masol(tesztelo, bevstring->sug);
                free(bevstring->sug);
                bevstring->sug = tesztelo;
            }
            else{
                strcpy(tesztelo, bevstring->sug);
                strcat(tesztelo, szam);
                if (atoi(tesztelo) <= sug_max){
                    free(bevstring->sug);
                    bevstring->sug = tesztelo;
                }
                else {
                    bevstring->sug[0] = '\0';
                    free(tesztelo);
                }
            }
            break;
        case Szazalek:
            if (szam_be == SDLK_BACKSPACE){
                egyel_kevesebb_masol(tesztelo, bevstring->szaz);
                free(bevstring->szaz);
                bevstring->szaz = tesztelo;
            }
            else{
                strcpy(tesztelo, bevstring->szaz);
                strcat(tesztelo, szam);
                if (atoi(tesztelo) <= szaz_max){
                    free(bevstring->szaz);
                    bevstring->szaz = tesztelo;
                }
                else {
                    bevstring->szaz[0] = '\0';
                    free(tesztelo);
                }
            }
            break;
        case Ido:
            if (szam_be == SDLK_BACKSPACE){
                egyel_kevesebb_masol(tesztelo, bevstring->ido);
                free(bevstring->ido);
                bevstring->ido = tesztelo;
            }
            else{
                strcpy(tesztelo, bevstring->ido);
                strcat(tesztelo, szam);
                if (atoi(tesztelo) <= ido_max){
                    free(bevstring->ido);
                    bevstring->ido = tesztelo;
                }
                else {
                    bevstring->ido[0] = '\0';
                    free(tesztelo);
                }
            }
            break;
        case Semmi:
            break;
    }
}