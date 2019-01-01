#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Graph.h"
#include "HandleEvent.h"
#include "Structs.h"
#include "Move.h"
#include "Logic.h"



int main() {
    int FPS = 50;
    SDL_Window* window;
    Tanks T;
    SetColor(&T);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            T.tank[i].bullet[j].haveShoten = 0;
            T.tank[i].bullet[i].alphax = 1;
            T.tank[i].bullet[i].alphay = 1;
        }
        T.tank[i].exist = 0;
        T.tank[i].Radius = 20;
        T.tank[i].x = T.tank[i].y = -50;
    }


    printf("Number Of Tanks: ");
    scanf("%d", &T.Number);


    Map map = GetMap();

    for (int k = 0; k < T.Number; ++k) {
        T.tank[k].exist = 1;
        T.tank[k].haveTouchedwall = 1;
        while (T.tank[k].haveTouchedwall){
            T.tank[k].x = rand() % (map.dx * map.scale);
            T.tank[k].y = rand() % (map.dy * map.scale);
            T.tank[k].angle = rand() % 57;
            TankTouchWall(&T, map.wall);
        }
    }


    init_window(&window, map.dx * map.scale, map.dy * map.scale);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



    // Check that the window was successfully created
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    while (handleEvents()){

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
        SDL_RenderClear(renderer);

        //...........................................................................................
        //Program Starts Here
        //...........................................................................................


        TankTouchWall(&T, map.wall);
        SetPermition(&T, map.wall);
        BulletTouchWall(&T, map.wall);
        BulletTouchTank(&T);


        if(T.tank[0].exist){
            moveTank1(&T.tank[0]);
            DrawTank(&renderer, &T.tank[0]);
        }
        if(T.tank[1].exist){
            moveTank2(&T.tank[1]);
            DrawTank(&renderer, &T.tank[1]);
        }
        if(T.tank[2].exist){
            moveTank3(&T.tank[2]);
            DrawTank(&renderer, &T.tank[2]);
        }
        if(T.tank[3].exist){
            moveTank4(&T.tank[3]);
            DrawTank(&renderer, &T.tank[3]);
        }
        DrawBullets(&renderer, &T);
        DrawMap(&renderer, map.wall);
        //...........................................................................................
        //...........................................................................................

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);

    }
    quit_window(&window);


    return 0;
}