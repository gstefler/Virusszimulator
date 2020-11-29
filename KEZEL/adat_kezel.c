#include "adat_kezel.h"

extern int W, H;

/*
 * Filenak a neve a hibaüzenetekhez
 * */
static const char* filenev = "adat_kezel.c:";

/*
 * Láncolt listát felszabadító függvény
 * A "mindent_szabadit" használja
 * */
static void graf_szabadit(Grafikon *g){
    GrafLista* szabadito = g->elso;
    while (szabadito != NULL){
        GrafLista *kov = szabadito->kov;
        free(szabadito);
        szabadito = kov;
    }
}

/* Ez a fv takarít utánunk, tehát felszabadít mindent
 * Belülről kifelé haladva
 * */
void mindent_szabadit(Szim **szim){
    Szim *tmp = *szim;
    for (int i = 0; i < SZIMSZAM; i++)
    {
        //először a népességet
        free(tmp[i].nep);
        //aztán a láncolt listát
        graf_szabadit(tmp[i].graf);
        //végül a láncolt listát tartalmazó típust
        free(tmp[i].graf);
    }
    //végül a szim tömbjét
    free(tmp);
    *szim = tmp;
}

/*
 * Ezt a függvényt csak a "Nepvaltoztat" használja
 * Feladata visszatérni egy véletlen sebességgel ami nem nulla
 * és a bemenetként kapott tartományban van( |veletlen_seb| = tart )
 * */
static double veletlen_seb(void){
    double seb = (double)rand() / RAND_MAX * 2.0 - 1.0;
    while ((int)(seb * 100) == 0)
        seb = (double)rand() / RAND_MAX *  2.0 - 1.0;
    return seb;
}

/*
 * Ez a fv szükséges minden szimuláció elindítása előtt.
 * Akkor fut le ha változtatni szeretnénk a szimulációnk népméretét
 * */
void nepvaltozat(Szim* szimulacio){
    if (szimulacio->graf->meret != 0) {
        graf_szabadit(szimulacio->graf);
        free(szimulacio->graf);
        szimulacio->graf = graf_init();
    }

    //Felszabadítja a régi népet(ha elszőr futtatjuk akkor az 0 volt)
    free(szimulacio->nep);
    //Lefoglal egy új népet a szimulációnk népméretének megfelelően
    szimulacio->nep = (Egyed*)malloc(szimulacio->nepmeret * sizeof(struct Egyed));
    /*
    Feltölti az összes egyedet véletlenszerű sebességgel és pozícióval
    plusz mindenkit Fogékonyra állít és nulláza a fertőzőttségi idejüket
    */
    for (int i = 0; i < szimulacio->nepmeret; ++i) {
        szimulacio->nep[i].hely.x = rand() % realtoint(W * (TART_SZEL * 2) + 1 - R);
        szimulacio->nep[i].hely.y = rand() % realtoint(W * TART_SZEL + 1 - R);
        szimulacio->nep[i].hely.vx = veletlen_seb();
        szimulacio->nep[i].hely.vy = veletlen_seb();
        szimulacio->nep[i].miota = 0;
        szimulacio->nep[i].mennyit = 0;
        szimulacio->nep[i].allapot = Fogekony;
    }
    //Végül az első egyedet Fertőzöttre állítja(valhogy el kell hogy induljon :D)
    szimulacio->nep[0].allapot = Fertozott;
}

/*
 * Grafikonban lévő láncolt lista inicializálása
 * Létrehoz egy első elemet amiben 1db fertőzött van,
 * mert ugye a 0. időpillanatban 1 fertőzött van
 * és ez a lista utolsó eleme(jelenleg)
 * */
Grafikon* graf_init(void){
    GrafLista *elso = (GrafLista*)malloc(sizeof(GrafLista));
    if (elso == NULL)
    {
        printf("%s GrafLista foglalási hiba!", filenev);
        exit(1);
    }

    elso->fert = 1;
    elso->gogyult = 0;
    elso->kov = NULL;

    Grafikon* tmp = (Grafikon*)malloc(sizeof(Grafikon));
    if (tmp == NULL)
    {
        printf("%s Grafikon foglalási hiba!", filenev);
        exit(1);
    }
    tmp->elso = elso;
    tmp->utso = elso;
    tmp->meret = 1;

    return tmp;
}

/*
 * Ez a legelső foglalás, ami szimulációkból álló tömböt hoz létre
 * A bemenetként kapott tömb-be foglalja bele
 * */
void foglal(Szim **s){
    Szim *tmps = (Szim*)malloc(SZIMSZAM * sizeof(Szim));
    if (tmps == NULL)
    {
        printf("%s Szim foglalási hiba!", filenev);
        exit(1);
    }


    for (int i = 0; i < SZIMSZAM; i++)
    {
        tmps[i].nepmeret = 10;
        /*
         * Minden egyes szimuláción belül lefoglalunk egy 0 méretű
         * Egyed* típúsú tömböt is hogy késöbb ezt csak átméretezni kelljen
         * */
        tmps[i].nep = (Egyed*)malloc(0 * sizeof(Egyed));
        if (tmps == NULL)
        {
            printf("%s Egyed foglalási hiba!", filenev);
            exit(1);
        }
        //szimuláció nem működő állapotba állítása
        tmps[i].all = false;
        //grafkion inicializálása
        tmps[i].graf = graf_init();
        nepvaltozat(&tmps[i]);
    }
    *s = tmps;
}