cmake_minimum_required(VERSION 3.17)
project(NHF C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(SDL_FV)


add_executable(NHF
        SDL_FV/sdl_init.c
        SDL_FV/sdl_init.h
        debugmalloc.h
        def.h
        main.c KEZEL/adat_kezel.c KEZEL/adat_kezel.h KEZEL/szimluacio_kezel.c KEZEL/szimluacio_kezel.h RAJZOL/szim_rajzol.c RAJZOL/szim_rajzol.h RAJZOL/graf_rajzol.c RAJZOL/graf_rajzol.h globalis_fvek.c globalis_fvek.h KEZEL/kattintas_kezel.c KEZEL/kattintas_kezel.h RAJZOL/dinamikus_elemek_rajzol.c RAJZOL/dinamikus_elemek_rajzol.h RAJZOL/osszes_rajzol.c RAJZOL/osszes_rajzol.h KEZEL/beallitas_kezel.c KEZEL/beallitas_kezel.h FILE/export_SVG.c FILE/export_SVG.h)

target_link_libraries(${PROJECT_NAME} m)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
