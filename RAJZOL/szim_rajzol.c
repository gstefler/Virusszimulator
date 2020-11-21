#include "szim_rajzol.h"

extern int W, H;
extern Betutipus* betutipus;

//ez a fv rajzolja ki a szimulációkat és azoknak tartalmát
void szim_rajzol(SDL_Renderer *renderer, Szim* const szimulacio, int i){
    for (int j = 0; j < szimulacio[i].nepmeret; ++j) {
        int x1 = realtoint(szimulacio[i].nep[j].hely.x + (W / 4 - W * TART_SZEL));
        int y1 = realtoint(szimulacio[i].nep[j].hely.y + i * (W * TART_SZEL + 50) + (H * SAV_SZEL + 50));
        switch (szimulacio[i].nep[j].allapot) {
            case Fertozott:
                filledCircleRGBA(renderer, x1, y1, R, 255, 0, 0, 255);
                aacircleRGBA(renderer, x1, y1, R, 255, 0, 0, 255);
                //aacircleRGBA(renderer, x1, y1, szimulacio[i].virus.r, 255, 0, 0, 255);
                break;
            case Gyogyult:
                filledCircleRGBA(renderer, x1, y1, R, 0, 255, 0, 255);
                aacircleRGBA(renderer, x1, y1, R, 0, 255, 0, 255);
                break;
            case Fogekony:
                filledCircleRGBA(renderer, x1, y1, R, 255, 255, 255, 255);
                aacircleRGBA(renderer, x1, y1, R, 255, 255, 255, 255);
                break;
        }
    }
}

void keret(SDL_Renderer *renderer, Szim* const szim, int i){
    int x1 = W / 4 - W * TART_SZEL;
    int y1 = H * SAV_SZEL + 50 + i * (W * TART_SZEL + 50);
    int x2 = x1 + W * TART_SZEL * 2;
    int y2 = y1 + W * TART_SZEL;
    if (szim[i].all){
        char szim_nev[20];
        sprintf(szim_nev, "%d. szimuláció", i + 1);
        SDL_Color vilagos = {220, 220, 220, 255};
        rectangleRGBA(renderer, x1, y1, x2, y2, 236, 236, 236, 255);
        kiir(renderer, betutipus[0].tipus, vilagos, szim_nev, x1, y1 - 25);
    } else{
        rectangleRGBA(renderer, x1, y1, x2, y2, 236, 236, 236, 120);
    }
}
