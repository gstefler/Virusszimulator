# Vírusszimulátor
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
