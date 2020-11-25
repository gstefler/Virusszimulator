#include "SVG.h"
#define SVG_GRAF_W 980
#define SVG_GRAF_H 350.0

static void pontok_stringbe(char** fert_string, char** gyogy_string, Grafikon* g, int const nepmeret){
    double novelo = (double)SVG_GRAF_W / g->meret;
    double arany = SVG_GRAF_H / nepmeret;
    /* 4: első koordináta max mérete
     * 4: másodi koordináta max mérete
     * 2: space és vessző
     * */
    int karakter_per_koordinata = 4 + 4 + 2;
    int koordinatak_szama = g->meret + 2;

    char* fert_pontok = (char*)malloc(koordinatak_szama * karakter_per_koordinata * sizeof(char));
    char* gyogy_pontok = (char*)malloc(koordinatak_szama * karakter_per_koordinata * sizeof(char));
    fert_pontok[0] = '\0';
    gyogy_pontok[0] = '\0';

    int x = 10;
    int y = 10 + (int)SVG_GRAF_H;

    Sint16* f_y = belerak(g, Fert, arany, nepmeret, novelo, x, y, 10);
    Sint16* gy_y = belerak(g, Gyogy, arany, nepmeret, novelo, x, y, 10);
    Sint16* f_gy_x = belerak(g, X_koo, arany, nepmeret, novelo, x, y, 10);

    char x_ko[4 + 1], y_ko[5 + 1];
    for (int i = 0; i < koordinatak_szama; ++i) {
        sprintf(x_ko, "%d", f_gy_x[i]);
        sprintf(y_ko, "%d ", f_y[i]);
        strcat(fert_pontok, x_ko);
        strcat(fert_pontok, ",");
        strcat(fert_pontok, y_ko);
        sprintf(x_ko, "%d", f_gy_x[i]);
        sprintf(y_ko, "%d ", gy_y[i]);
        strcat(gyogy_pontok, x_ko);
        strcat(gyogy_pontok, ",");
        strcat(gyogy_pontok, y_ko);
    }
    free(*fert_string);
    free(*gyogy_string);
    free(f_y);
    free(gy_y);
    free(f_gy_x);
    *fert_string = fert_pontok;
    *gyogy_string = gyogy_pontok;

}

void SVG_export(Szim* const szim, int melyik){
    FILE* exp_svg;
    char* fertpontok = (char*)malloc(0);
    char* gyogypontok = (char*)malloc(0);
    pontok_stringbe(&fertpontok, &gyogypontok, szim[melyik].graf, szim[melyik].nepmeret);
    char filenev[12 + 1];

    sprintf(filenev, "szim_%d.svg", melyik);
    exp_svg = fopen(filenev, "w");
    if (exp_svg != NULL){
        printf("Sikeres filemegnyitás!\n");
    } else{
        printf("File megnyitási hiba!\n");
        exit(1);
    }
    fprintf(exp_svg,
            "<svg version=\"1.1\"\n"
            "     baseProfile=\"full\"\n"
            "     width=\"1000\" height=\"500\"\n"
            "     xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(exp_svg, "<rect width=\"100%%\" height=\"100%%\" fill=\"#3e96fa\" />\n");
    fprintf(exp_svg, "<polygon points=\"%s\" style=\"fill:red;\" />\n", fertpontok);
    fprintf(exp_svg, "<polygon points=\"%s\" style=\"fill:green;\" />\n", gyogypontok);
    fprintf(exp_svg, "</svg>");
    free(fertpontok);
    free(gyogypontok);
    fclose(exp_svg);
}