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
    int export_szamlalo = 0;

    int bet_db = 4;
    betutipus = (Betutipus*)malloc(bet_db * sizeof(Betutipus));
    betutipus[0].meret = 20;
    betutipus[1].meret = 16;
    betutipus[2].meret = 40;
    betutipus[3].meret = 12;

    Bevstring bev;
    bev.nep[0] = '\0';
    bev.sug[0] = '\0';
    bev.szaz[0] = '\0';
    bev.ido[0] = '\0';

    foglal(&szim);
    init_SDL();
    init_TTF(betutipus, bet_db);

    /*
    szim->all = true;
    szim->nepmeret = 1000;
    szim->virus = (Virus){20, 0.3, 8};
    nepvaltozat(szim);*/

    SDL_Window* window;
    SDL_Renderer* renderer;
    create(&window, &renderer);

    //időzítő
    int s = 0;
    SDL_TimerID base = SDL_AddTimer(fps, idozit, NULL);

    //Eseményvezérelt LOOP
    //változó ami a szimulációt szüneteltetheti
    bool stop = false;
    //melyik szimulációval foglalkozunk
    int melyik;
    //kilépés
    bool quit = false;
    //hibaváltozó
    Error hiba;
    while (!quit){
        SDL_Event ev;
        SDL_WaitEvent(&ev);
        switch (ev.type) {
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&EX, &EY);
                break;
            case SDL_MOUSEBUTTONUP:
                if (beallit){
                    megse();
                    bevitel_valaszt();
                    inditas(szim, melyik, &bev, &stop, &hiba);
                }
                else{
                    beall(szim, &stop, &melyik);
                    torol(szim);
                    ujraindit(szim);
                    uj(szim, &stop, &melyik);
                    svg_export_katt(szim, &export_szamlalo);
                }
                kilepes(&quit);
                break;
            case SDL_KEYUP:
                if (beallit && bevitel != Semmi && billentyutochar(ev.key.keysym.sym) >= '0'
                && billentyutochar(ev.key.keysym.sym) <= '9' || ev.key.keysym.sym == SDLK_RETURN
                || ev.key.keysym.sym == SDLK_BACKSPACE || ev.key.keysym.sym == SDLK_KP_ENTER){
                    bevisz(&bev, ev.key.keysym.sym);
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
                rajzolas(renderer, szim, bev, melyik, hiba, stop);
                if (!stop){
                    if (s++ < 1000 / fps) {
                        szimulal(szim, false);
                    }
                    else{
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
