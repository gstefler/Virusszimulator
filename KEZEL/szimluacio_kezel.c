#include "szimluacio_kezel.h"

extern int W, H;

/*
Paraméterként egy szimulációt kap és vissza tér az adott szimulációban
a fertőzöttek számával
*/
static int fertozottek(Szim* const szim){
    int osszeg = 0;
    for (int i = 0; i < szim->nepmeret; i++)
    {
        if (szim->nep[i].allapot == Fertozott)
            osszeg++;
    }
    return osszeg;
}

/*
Paraméterként egy szimulációt kap és vissza tér az adott szimulációban
a gyógyultak számával
*/
static int gyogyultak(Szim* const szim){
    int osszeg = 0;
    for (int i = 0; i < szim->nepmeret; i++)
    {
        if (szim->nep[i].allapot == Gyogyult)
            osszeg++;
    }
    return osszeg;
}

/*
Ez a függvény bővíti a láncolt listát az adott pillanat beli adatokkal
amiket a függvény paraméterként kap meg
*/
void bovit(Szim* szim, int const fert, int const gyogy){
    if (szim->graf->utso != NULL){
        GrafLista* uj = (GrafLista*)malloc(sizeof(GrafLista));
        uj->fert = fert;
        uj->gogyult = gyogy;
        uj->kov = NULL;

        szim->graf->utso->kov = uj;
        szim->graf->utso = uj;

        szim->graf->meret++;
    }
}

/*
megnézi hogy két egyed egy bizonyos távolságon belül van-e
bemenet: 2 egyed koordinátája és sugara, a tesztelő egyed sugara(r2)
és a virus terjedési sugara(r1)
*/
static bool kozel(double x1, double y1, double x2,double y2, int r1, int r2){
    double dx = x1 - x2;
    double dy = y1 - y2;
    double d = sqrt((double)(dx*dx + dy*dy));
    return d < r1 + r2;
}

/*
A bemenő vírus paramétere alapján visszatér egy fertőzött vagy fogékony állapottal
*/
static Allapot fertoz(Virus* const v){
    double p = v->p;
    if (((double)(rand() % 100)) / 100 <= p){
        return Fertozott;
    }
    return Fogekony;
}

/*
Ez a függvény adott időközönkén hívódik meg és akkor megnézi, hogy az egymáshoz
közel lévő emberek a virus paramétere szerint fertőzőttek lesznek-e,
ha meggyógyulnak azt is kezeli
*/
static void tesztel(Szim* szimulacio, int i){
    //rögzíti hogy az előző időpillanatban mennyi volt a fertőzött
    szimulacio[i].elozo = fertozottek(szimulacio);
    Egyed* nep = szimulacio[i].nep;
    //végig megyünk az összes egyeden
    for (int j = 0; j < szimulacio[i].nepmeret; ++j) {
        //ha fertőzött
        if (nep[j].allapot == Fertozott){
            //megnézzük hogy lejárt-e a fertőzésvés növeljük
            if (++nep[j].miota == szimulacio[i].virus.recover){
                //ha lejárt megyógyultak
                nep[j].allapot = Gyogyult;
            }
            else{
                //végig megyünk a maradék egyedeken
                for (int k = j + 1; k <szimulacio[i].nepmeret; ++k) {
                    //fogékony és közel van
                    if (nep[k].allapot == Fogekony &&
                        kozel(nep[j].hely.x, nep[j].hely.y, nep[k].hely.x, nep[k].hely.y, szimulacio[i].virus.r, R)){

                        nep[k].allapot = fertoz(&szimulacio[i].virus);
                        if (nep[k].allapot == Fertozott)
                            nep[j].mennyit++;
                    }
                }
            }
        }
    }
}

/*
Ez a fv számolja ki a helyzetét az egyedeknek
És a paraméterként kapott Hely*-ba írja bele
*/
static void seb_szam(Hely *hely){
    double *x = &hely->x;
    double *y = &hely->y;
    double *xv = &hely->vx;
    double *yv = &hely->vy;
    if (*x + *xv <= 0 + R && *xv < 0){
        *x -= 0 + *x - R - 2;
        *xv *= -1;
    }
    else if (*x + *xv >= 0 + (W * TART_SZEL * 2) - R && *xv > 0){
        *x += (W * TART_SZEL * 2) - *x - R - 2;
        *xv *= -1;
    }
    else
        *x += *xv;
    if (*y + *yv <= 0 + R && *yv < 0){
        *y -= 0 + *y - R - 2;
        *yv *= -1;
    }
    else if (*y + *yv >= 0 + (W * TART_SZEL) - R &&  *yv > 0){
        *y += (W * TART_SZEL) - *y - R - 2;
        *yv *= -1;
    }
    else
        *y += *yv;
}

static void r_szamol(Szim* szim, int i){
    double uj_r0 = 0;
    if (szim[i].elozo != 0)
        uj_r0 = (double)szim[i].graf->utso->fert / (double)szim[i].elozo;

    if (szim[i].rmax < uj_r0)
        szim[i].rmax = uj_r0;
    if (szim[i].graf->utso->fert != 0){
        szim[i].R0 = uj_r0;
    }
}

/*
Ítt gyűlik össze az összes szimulációhoz szükséges függvény
és fut le a megfelelő sorrendben
*/
void szimulal(Szim* szimulacio, bool mindent){
    for (int i = 0; i < SZIMSZAM; ++i) {
        if (szimulacio[i].all && szimulacio[i].graf->utso->fert != 0){
            if (mindent) {
                tesztel(szimulacio, i);
                bovit(&szimulacio[i], fertozottek(&szimulacio[i]), gyogyultak(&szimulacio[i]));
                r_szamol(szimulacio, i);
            }
            for (int j = 0; j < szimulacio[i].nepmeret; ++j){
                seb_szam(&szimulacio[i].nep[j].hely);
            }
        }
    }
}