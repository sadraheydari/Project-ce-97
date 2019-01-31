//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_HANDLEEVENT_H
#define ALTERTANK_HANDLEEVENT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Graph.h"



int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 0;

    }
    return 1;
}

int handleStartMenu(Menu* mnu){
    SDL_Event event;
    SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) {
            mnu->ForceExit = 1;
            return 0;
        }
        if (event.type == SDL_KEYDOWN){
            SDL_Keycode key = event.key.keysym.sym ;
            if ( key == SDLK_RETURN)
                return 0;
            if (key == SDLK_DOWN || key == SDLK_UP){
                mnu->LoadStart = 1 - mnu->LoadStart;
                mnu->NewGame = 1 - mnu->NewGame;
            }
        }
        return 1;

}

int handleMinMenu(Menu* mnu){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) {
        mnu->ForceExit = 1;
        return 0;
    }

    if (event.type == SDL_KEYUP){
        SDL_Keycode key = event.key.keysym.sym ;
        if ( key == SDLK_ESCAPE ) {
            mnu->Exit = mnu->SaveGame = 0;
            return 0;
        }
    }

    if (event.type == SDL_KEYDOWN){
        SDL_Keycode key = event.key.keysym.sym ;
        if ( key == SDLK_RETURN ) {
            return 0;
        }
        if (key == SDLK_DOWN){


            if(!(mnu->Exit || mnu->SaveGame)){
                mnu->SaveGame = 1;
                mnu->Exit = 0;
                return 1;
            }
            if(mnu->Exit){
                mnu->SaveGame = 0;
                mnu->Exit = 0;
                return 1;
            }
            if(mnu->SaveGame){
                mnu->SaveGame = 0;
                mnu->Exit = 1;
                return 1;
            }
        }
        if (key == SDLK_UP){

            if(!(mnu->Exit || mnu->SaveGame)){
                mnu->SaveGame = 0;
                mnu->Exit = 1;
                return 1;
            }
            if(mnu->Exit){
                mnu->SaveGame = 1;
                mnu->Exit = 0;
                return 1;
            }
            if(mnu->SaveGame){
                mnu->SaveGame = 0;
                mnu->Exit = 0;
                return 1;
            }

        }
    }
    return 1;
}

int handleSelectMap(Menu* mnu){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) {
        mnu->ForceExit = 1;
        return 0;
    }
    if (event.type == SDL_KEYDOWN){
        SDL_Keycode key = event.key.keysym.sym ;
        if ( key == SDLK_RETURN)
            return 0;
        if (key == SDLK_LEFT || key == SDLK_RIGHT){
            mnu->promap = 1 - mnu->promap;
            mnu->simplemap = 1 - mnu->simplemap;
        }
    }
    return 1;
}


#endif //ALTERTANK_HANDLEEVENT_H
