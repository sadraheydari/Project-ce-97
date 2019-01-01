//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_GRAPH_H
#define ALTERTANK_GRAPH_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Structs.h"



void init_window(SDL_Window** window, int deltax, int deltay){

    *window = SDL_CreateWindow("Sadra AlterTank",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                deltax,
                                deltay,
                                SDL_WINDOW_OPENGL);
}

void quit_window(SDL_Window** window){

    SDL_DestroyWindow(*window);
    SDL_Quit();
}

void DrawTank(SDL_Renderer** rend, Tank* tank){

    //Draw Main Circle
    filledCircleRGBA(*rend, tank->x, tank->y, tank->Radius, tank->clr.r, tank->clr.g, tank->clr.b, 150);
    filledCircleRGBA(*rend, tank->x, tank->y, tank->Radius * 2 / 3, 150, 150, 150, 255);

    filledCircleRGBA(*rend, tank->x, tank->y, tank->Radius * 4 / 5, tank->clr.r, tank->clr.g, tank->clr.b, 150);
    //Remove Part of Main Circle
    thickLineRGBA(*rend, tank->x, tank->y, tank->x + tank->Radius * cos(tank->angle) * 1.05,
                  tank->y + tank->Radius * sin(tank->angle) * 1.05, 15, 150, 150, 150, 255);
    //Draw Second Circle
    filledCircleRGBA(*rend, tank->x, tank->y, tank->Radius / 2, tank->clr.r, tank->clr.g, tank->clr.b, 255);
    //Draw Pipe of Tank
    thickLineRGBA(*rend, tank->x, tank->y, tank->x + tank->Radius * cos(tank->angle),
                  tank->y + tank->Radius * sin(tank->angle), 5, tank->clr.r/2, tank->clr.g/2, tank->clr.b/2, 255);
}

void DrawMap(SDL_Renderer** rend, Wall wall){
    for (int i = 0; i < wall.n; ++i) {
        thickLineRGBA(*rend, wall.x1[i], wall.y1[i], wall.x2[i], wall.y2[i], 2, 10, 10, 10, 255);
    }
}

void DrawBullets(SDL_Renderer** rend, Tanks* T){

    int speed = 7;
    int BulletLife = 5000;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            if( T->tank[i].bullet[j].haveShoten ){
                filledCircleRGBA(*rend, T->tank[i].bullet[j].x, T->tank[i].bullet[j].y, 3, 20, 20, 20, 255);
                T->tank[i].bullet[j].x += speed * cos(T->tank[i].bullet[j].angle) * T->tank[i].bullet[j].alphax;
                T->tank[i].bullet[j].y += speed * sin(T->tank[i].bullet[j].angle) * T->tank[i].bullet[j].alphay;
                if( (SDL_GetTicks() - T->tank[i].bullet[j].LastShot) > BulletLife )
                    T->tank[i].bullet[j].haveShoten = 0;
            }

        }
    }
}


#endif //ALTERTANK_GRAPH_H
