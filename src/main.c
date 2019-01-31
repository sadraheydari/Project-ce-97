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
    Map map;
    Tanks T;
    Pop power; power.exist = 0; power.time = 0;
    int FPS = 50;
    SDL_Window* window;
    Escape esc; esc.exist = 0; esc.time = 0;
    Menu mnu; mnu.NewGame = 1; mnu.LoadStart = 0; mnu.ForceExit = 0; mnu.promap = 0; mnu.simplemap = 1;
    T.Number = 2;
    T.tank[0].laser.exist = 0;
    T.tank[1].laser.exist = 0;
    T.tank[0].laser.shoot = 0;
    T.tank[1].laser.shoot = 0;
    //Set Color ...................................
    color red, blue;
    red.r = 100; red.g = red.b = 0;
    blue.r = blue.g = 0; blue.b = 100;
    T.tank[0].clr = blue;
    T.tank[1].clr = red;
    //............................................



    init_window(&window, 680, 600);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Check that the window was successfully created
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }


    //Start Menu ...........................................
    while (handleStartMenu(&mnu)){
        DrawStartMenu(&renderer, mnu);
    }
    if(mnu.ForceExit){quit_window(&window); return 0;}
    SDL_Delay(500);
    //......................................................



    if(mnu.NewGame){ //New Game Starts ....................
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

        while (handleSelectMap(&mnu)){
            DrawSelectMapMenu(&renderer, mnu);
        }
        if(mnu.ForceExit){quit_window(&window); return 0;}

        map = GetMap(mnu);

        for (int k = 0; k < T.Number; ++k) {
            T.tank[k].exist = 1;
            T.tank[k].ShootTime = 0;
            T.tank[k].score = 0;
            T.tank[k].haveTouchedwall = 1;
            while (T.tank[k].haveTouchedwall){
                T.tank[k].x = rand() % (map.dx * map.scale);
                T.tank[k].y = rand() % (map.dy * map.scale);
                T.tank[k].angle = rand() % 57;
                TankTouchWall(&T, map.wall);
            }
        }

    }//....................................................

    if(mnu.LoadStart){
        LoadGame(&T, &mnu);
        map = GetMap(mnu);
    }


    while (handleEvents()) {
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
        SDL_RenderClear(renderer);

        //...........................................................................................
        //Program Starts Here
        //...........................................................................................

        if(esc.exist){
            mnu.Exit = mnu.SaveGame = 0;
            while (handleMinMenu(&mnu)){
               DrawMinMenu(&renderer, mnu, T);
            }
            esc.exist = 0;
            if(mnu.SaveGame){ SaveGame(T, mnu);}
            if(mnu.ForceExit || mnu.Exit || mnu.SaveGame){quit_window(&window); return 0;}
        }

        TankTouchWall(&T, map.wall);
        SetPermition(&T, map.wall);
        BulletTouchWall(&T, map.wall);
        BulletTouchTank(&T);


        if (T.tank[0].exist) {
            moveTank1(&T.tank[0], &esc);
            DrawTank(&renderer, &T.tank[0]);
        }
        if (T.tank[1].exist) {
            moveTank2(&T.tank[1], &esc);
            DrawTank(&renderer, &T.tank[1]);
        }

        if((!(power.exist)) && SDL_GetTicks() - power.time > 15000 ){ power.exist = 1; SetPopUp(&power, map.wall);}


        DrawPopUP(&renderer, power);
        LaserTouchWall(&T, map.wall);
        TankEatPopUP(&power, &T);
        RefreshGame(&T, map);
        DrawBullets(&renderer, &T);
        DrawMap(&renderer, map.wall, 1);
        DrawScore(&renderer, T);
        DrawShotenLaser(&renderer, &T);
        DrawLaser(&renderer,&T);
        //...........................................................................................
        //...........................................................................................

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);

    }

    quit_window(&window);


    return 0;
}