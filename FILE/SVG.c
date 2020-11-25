#include "SVG.h"
#define SVG_GRAF_W 760
#define SVG_GRAF_H 400

/* Belemásolja a már lefutott szimuláció grafikonjának az adatait
 * a bemenetként kapott fert_string és gyogy_string-be
 * hasonlóan működik a graf_rajzol.c fileban található gorbe_rajzol függvényhez
 * csak ez SVG-filera van írva
 * */
static void pontok_stringbe(char** fert_string, char** gyogy_string, Grafikon* g, int const nepmeret){
    double novelo = (double)SVG_GRAF_W / g->meret;
    double arany = (double)SVG_GRAF_H / nepmeret;

    /* felső becslés a karakterek hosszára:
     * 4: első koordináta max mérete
     * 4: másodi koordináta max mérete
     * 2: space és vessző
     * */
    int karakter_per_koordinata = 4 + 4 + 2;
    int koordinatak_szama = g->meret + 2;

    //átmeneti stringek foglalása
    char* fert_pontok = (char*)malloc(koordinatak_szama * karakter_per_koordinata * sizeof(char));
    char* gyogy_pontok = (char*)malloc(koordinatak_szama * karakter_per_koordinata * sizeof(char));
    //nullázás
    fert_pontok[0] = '\0';
    gyogy_pontok[0] = '\0';

    int x = 20;
    int y = 20 + SVG_GRAF_H;

    /* A grafikon kirajzolásához hasonlóan bejárjuk a láncolt listát
     * és belerakjuk a tömbe a megfelelő koordinátákat
     * */
    Sint16* f_y = belerak(g, Fert, arany, SVG_GRAF_W, novelo, x, y, 20);
    Sint16* gy_y = belerak(g, Gyogy, arany, SVG_GRAF_W, novelo, x, y, 20);
    Sint16* f_gy_x = belerak(g, X_koo, arany, SVG_GRAF_W, novelo, x, y, 20);

    /* Ezekbe a stringekbe másoljuk az adott X, Y koordinátákat*/
    char x_ko[4 + 1], y_ko[5 + 1];
    for (int i = 0; i < koordinatak_szama; ++i) {
        //Fertőzöttek bemásolása
        sprintf(x_ko, "%d", f_gy_x[i]);
        sprintf(y_ko, "%d ", f_y[i]);
        strcat(fert_pontok, x_ko);
        strcat(fert_pontok, ",");
        strcat(fert_pontok, y_ko);
        //**********************
        //Gyógyultak bemásolása
        sprintf(x_ko, "%d", f_gy_x[i]);
        sprintf(y_ko, "%d ", gy_y[i]);
        strcat(gyogy_pontok, x_ko);
        strcat(gyogy_pontok, ",");
        strcat(gyogy_pontok, y_ko);
        //***********************
    }
    //szabadítás
    free(*fert_string);
    free(*gyogy_string);
    free(f_y);
    free(gy_y);
    free(f_gy_x);
    //pointerek átállítása
    *fert_string = fert_pontok;
    *gyogy_string = gyogy_pontok;

}

/* Elvégzi az SVG file exportálását
 * megkapja a szimulációk tömbjét és hogy melyiket exportálja ki
 * */
void SVG_export(Szim* const szim, int melyik){
    FILE* exp_svg;
    char* fertpontok = (char*)malloc(0);
    char* gyogypontok = (char*)malloc(0);
    pontok_stringbe(&fertpontok, &gyogypontok, szim[melyik].graf, szim[melyik].nepmeret);

    //egyedi filenev, hogy egy futás alatt többet is ki tudjunk exportálni
    char filenev[12 + 1];
    sprintf(filenev, "szim_%d.svg", melyik);
    exp_svg = fopen(filenev, "w");
    if (exp_svg != NULL){
        printf("Sikeres filemegnyitás!\n");
    }
    else {
        printf("File megnyitási hiba!\n");
        exit(1);
    }

    /*SVG beleírása a fileba*/
    int x1 = 20;
    int y1 = 20;
    fprintf(exp_svg,
            "<svg version=\"1.1\"\n"
            "     baseProfile=\"full\"\n"
            "     width=\"800\" height=\"600\"\n"
            "     xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(exp_svg, "<rect width=\"100%%\" height=\"100%%\" fill=\"#202020\" />\n");
    fprintf(exp_svg, "<polygon points=\"%s\" style=\"fill:red;\" />\n", fertpontok);
    fprintf(exp_svg, "<polygon points=\"%s\" style=\"fill:green;\" />\n", gyogypontok);
    fprintf(exp_svg, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(220,220,220);stroke-width:2\" />", x1, y1, x1, y1 + SVG_GRAF_H);
    fprintf(exp_svg, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(220,220,220);stroke-width:2\" />", x1, y1 + SVG_GRAF_H, x1 + SVG_GRAF_W, y1 + SVG_GRAF_H);
    fprintf(exp_svg, "<text x=\"%d\" y=\"%d\" fill=\"white\" font-size=\"16\">fertőzöttek / gyógyultak</text>\n", x1 + 10, y1 + 10);
    fprintf(exp_svg, "<text x=\"%d\" y=\"%d\" fill=\"white\" text-anchor=\"end\" font-size=\"16\">idő</text>\n", x1 + SVG_GRAF_W, y1 + SVG_GRAF_H + 20);
    fprintf(exp_svg, "</svg>");

    //szoki szabadítás
    free(fertpontok);
    free(gyogypontok);
    fclose(exp_svg);
}