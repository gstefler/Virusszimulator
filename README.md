# Vírusszimulátor
![static image](https://github.com/steflergabor/Virusszimulator/blob/main/img/program.png)
![szim gif](https://github.com/steflergabor/Virusszimulator/blob/main/img/szim.gif)
## Feladat:
Egy olyan program készítése amely képes bizonyos kereteken belül egy vírus terjedését leszimulálni.
A kész programban a felhasználó képes egyszerre három egymástól különböző szimulációt futtatni, ezeknek a méretét változtatni.
Ezeken kívül a felhasználó az adott szimulációban terjedő vírus paramétereit is szabadon változtathatja. Ezek közé tartozik a vírus terjedési sugara, azaz mekkora körben van esély a fertőzésre, a fertőzés esélye, és az az idő ami alatt meg lehet belőle gyógyulni.
## Kezelés
A programban egyszerre három szimuláció tud működni. Kezdéskor mindegyik alvó állapotban van. Az új gombra kattintva lehet az adott szimulációt inicializálni(a fent említett paramétereket állítani) a megfelelő adatokkal és elindítani.
Minden aktív szimuláció mellé kirajzolódik egy grafikon ami a mellete lévő szimuláció fertőzött / gyógyult arányát rajzolja ki az idő függvényében. Ha egy szimuláció lefutott és vége van akkor ki lehet exportálni a kész grafikont egy **SVG** fileba a fontosabb adatokkal együtt. Bármelyik szimuláció bármikor törölhető, újraindítható, vagy változtatható.
## Shortcutok
1. **ESC** - kilép a programból, vagy ha a beállításokban vagyunk akkor abból
2. **SPACE** - a szüneteltetés megszüntetése vagy aktiválása
## Programozói rész
A programot linux alatt a *CLion IDE* segítségével készítettem. Használt könyvtárak: **SDL2**
Az összes függvény működésének részletes leírása megtalálható a kódban.
**Fontos**, hogy legyen a betűtípus az executable mellet font.ttf néven, különben nem fog elindulni!
## **Futtatás**
> Ha nem szeretnél bajlódni a fordítással, töltsd le a neked megfelelő release-t!
#### **Windows:** 
> [SDL2](http://libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz)
> [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15-win32-x64.zip)
> [SDL2_gfx](https://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/) (MinGW64)

**MinGW64:** `gcc -g *.c -o szimulator.exe -I<path to SDL2 include dirs> -L<path to SDL2 lib dirs> -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_gfx -O3 -fopenmp`

#### **Linux**
> SDL2 letöltése **GCC**-hez: `sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`

**GCC:** ```gcc -g *.c -o szimulator `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf```
## SVG Output
![exportsvg](https://github.com/steflergabor/Virusszimulator/blob/main/img/szim_0_x0.svg)
