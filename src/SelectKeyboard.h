//
// Created by sadra on 1/29/19.
//

#ifndef ALTERTANK_SELECTKEYBOARD_H
#define ALTERTANK_SELECTKEYBOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Structs.h"
#include "Logic.h"
#include "Graph.h"

void SelectKey(SDL_Window** window){
    SDL_Renderer* rend = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);



    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) {
        quit_window(window);
        return;
    }
    if (event.type == SDL_KEYDOWN){
        SDL_Keycode key = event.key.keysym.sym ;
        if ( key == SDLK_RETURN)
            return ;
        if (key == SDLK_DOWN || key == SDLK_UP){
            mnu->LoadStart = 1 - mnu->LoadStart;
            mnu->NewGame = 1 - mnu->NewGame;
        }
    }
    return;

}




#endif //ALTERTANK_SELECTKEYBOARD_H
