#include "def.h"
#include "KEZEL/adat_kezel.h"
#include "SDL_FV/sdl_init.h"
#include "KEZEL/szimluacio_kezel.h"
#include "RAJZOL/osszes_rajzol.h"
#include "KEZEL/kattintas_kezel.h"
#include "KEZEL/beallitas_kezel.h"

int W, H;
int EX, EY;
bool beallit = false;
Betutipus* betutipus;
Bevitel bevitel = Semmi;

int main(int argc, char *argv[]){
    int fps = 25;
    srand(time(0));
    Szim* szim;

    int bet_db = 4;
    betutipus = (Betutipus*)malloc(bet_db * sizeof(Betutipus));
    betutipus[0].meret = 20;
    betutipus[1].meret = 16;
    betutipus[2].meret = 40;
    betutipus[3].meret = 12;

    Bevstring* bevstring = (Bevstring*)malloc(sizeof(Bevstring));
    bevstring->nep = (char*)malloc(7 * sizeof(char));
    bevstring->sug = (char*)malloc(7 * sizeof(char));
    bevstring->szaz = (char*)malloc(7 * sizeof(char));
    bevstring->ido = (char*)malloc(7 * sizeof(char));
    bevstring->nep[0] = '\0';
    bevstring->sug[0] = '\0';
    bevstring->szaz[0] = '\0';
    bevstring->ido[0] = '\0';

    foglal(&szim);
    init_SDL();
    init_TTF(betutipus, bet_db);

    SDL_Window* window;
    SDL_Renderer* renderer;
    create(&window, &renderer);

    /*
    szim->all = true;
    szim->virus = (Virus){40, 0.3, 8};
    szim->nepmeret = 1000;
    nepvaltozat(szim);
    szim[1].all = true;
    szim[1].virus = (Virus){25, 0.3, 8};
    szim[1].nepmeret = 1000;
    nepvaltozat(&szim[1]);
    szim[2].all = true;
    szim[2].virus = (Virus){15, 0.3, 8};
    szim[2].nepmeret = 1000;
    nepvaltozat(&szim[2]);*/

    int s = 0;
    SDL_TimerID base = SDL_AddTimer(fps, idozit, NULL);


    //Eseményvezérelt LOOP
    bool stop = false;
    int melyik;
    bool quit = false;
    while (!quit){
        SDL_Event ev;
        SDL_WaitEvent(&ev);
        switch (ev.type) {
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&EX, &EY);
                break;
            case SDL_MOUSEBUTTONUP:
                kilepes(&quit);
                valt(szim, &stop, &melyik);
                torol(szim);
                ujraindit(szim);
                uj(szim, &stop, &melyik);
                bevitel_valaszt();
                inditas(szim, melyik, bevstring, &stop);
                break;
            case SDL_KEYUP:
                if (beallit && bevitel != Semmi && ev.key.keysym.sym <= 57 && ev.key.keysym.sym >= 48
                || ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_BACKSPACE){
                    bevisz(szim, bevstring, ev.key.keysym.sym);
                }
                if (ev.key.keysym.sym == SDLK_ESCAPE){
                    if (beallit)
                        beallit = false;
                    else
                        quit = true;
                }
                if (!beallit && ev.key.keysym.sym == SDLK_SPACE){
                    if (!stop)
                        stop = true;
                    else
                        stop = false;
                }
                break;
            case SDL_USEREVENT:
                rajzolas(renderer, szim, bevstring, melyik);
                if (!stop){
                    if (s++ < 1000 / fps) {
                        szimulal(szim, false);
                    }
                    else{
                        tesztel(szim);
                        szimulal(szim, true);
                        s = 0;
                    }
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    free(bevstring->nep);
    free(bevstring->sug);
    free(bevstring->szaz);
    free(bevstring->ido);
    free(bevstring);
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    mindent_szabadit(&szim);
    for (int i = 0; i < bet_db; ++i) {
        TTF_CloseFont(betutipus[i].tipus);
    }
    free(betutipus);
    SDL_Quit();
    return 0;
}