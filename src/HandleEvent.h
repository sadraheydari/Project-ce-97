//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_HANDLEEVENT_H
#define ALTERTANK_HANDLEEVENT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 0;
    }
    return 1;
}

void SetColor(Tanks* T){
    T->tank[0].clr.r = 0;
    T->tank[0].clr.g = 0;
    T->tank[0].clr.b = 100;

    T->tank[1].clr.r = 100;
    T->tank[1].clr.g = 0;
    T->tank[1].clr.b = 0;

    T->tank[2].clr.r = 0;
    T->tank[2].clr.g = 100;
    T->tank[2].clr.b = 0;

    T->tank[3].clr.r = 100;
    T->tank[3].clr.g = 100;
    T->tank[3].clr.b = 0;
}

#endif //ALTERTANK_HANDLEEVENT_H
