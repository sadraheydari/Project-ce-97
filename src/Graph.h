//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_GRAPH_H
#define ALTERTANK_GRAPH_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Structs.h"
#include "Logic.h"

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
                  tank->y + tank->Radius * sin(tank->angle) * 1.05,tank->Radius * 15/20, 150, 150, 150, 255);
    //Draw Second Circle
    filledCircleRGBA(*rend, tank->x, tank->y, tank->Radius / 2, tank->clr.r, tank->clr.g, tank->clr.b, 255);
    //Draw Pipe of Tank
    thickLineRGBA(*rend, tank->x, tank->y, tank->x + tank->Radius * cos(tank->angle),
                  tank->y + tank->Radius * sin(tank->angle), 5, tank->clr.r/2, tank->clr.g/2, tank->clr.b/2, 255);

}

void DrawMap(SDL_Renderer** rend, Wall wall, int black){
    for (int i = 0; i < wall.n; ++i) {
        if(black){thickLineRGBA(*rend, wall.x1[i], wall.y1[i], wall.x2[i], wall.y2[i], 3, 10, 10, 10, 255);}
        else{thickLineRGBA(*rend, wall.x1[i], wall.y1[i], wall.x2[i], wall.y2[i], 3, 200, 100, 0, 255);}
    }
}

void DrawBullets(SDL_Renderer** rend, Tanks* T){

    int speed = 4;
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

void DrawScore(SDL_Renderer** rend, Tanks T){
    Tank t1, t2;
    char* buffer = malloc(sizeof(char) * 50);
    double scale = 2;
    int neg;
    if(T.tank[0].score > 9)
        neg = 7;
    else
        neg = 2;
    sprintf(buffer, "%d", T.tank[0].score);
    SDL_RenderSetScale(*rend, scale, scale);
    stringRGBA(*rend, 640/scale - neg, 95/scale, buffer, T.tank[0].clr.r, T.tank[0].clr.g, T.tank[0].clr.b, 200);
    SDL_RenderSetScale(*rend, 1, 1);
    if(T.tank[1].score > 9)
        neg = 7;
    else
        neg = 2;
    sprintf(buffer, "%d", T.tank[1].score);
    SDL_RenderSetScale(*rend, scale, scale);
    stringRGBA(*rend, 640/scale - neg, 495/scale, buffer, T.tank[1].clr.r, T.tank[1].clr.g, T.tank[1].clr.b, 200);
    SDL_RenderSetScale(*rend, 1, 1);
    free(buffer);

    //ALTER TANK
    scale = 3;
    SDL_RenderSetScale(*rend, scale, scale);
    stringRGBA(*rend, 635/scale, 150/scale,"A", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 180/scale,"L", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 210/scale,"T", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 240/scale,"E", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 270/scale,"R", 0, 0, 0, 200);

    stringRGBA(*rend, 635/scale, 330/scale,"T", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 360/scale,"A", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 390/scale,"N", 0, 0, 0, 200);
    stringRGBA(*rend, 635/scale, 420/scale,"K", 0, 0, 0, 200);
    SDL_RenderSetScale(*rend, 1, 1);



    t1 = T.tank[0];
    t2 = T.tank[1];
    t1.x = t2.x = 640;
    t1.y = 50;
    t2.y = 550;
    t1.angle = 3.1415/4;
    t2.angle = 7*3.1415/4;
    DrawTank(rend, &t1);
    DrawTank(rend, &t2);
    if(t1.laser.exist){filledCircleRGBA(*rend, 650,  50, 5, 200, 100, 50, 255);}
    if(t2.laser.exist){filledCircleRGBA(*rend, 650, 550, 5, 200, 100, 50, 255);}
}

void DrawStartMenu(SDL_Renderer** rend, Menu mnu){

    SDL_SetRenderDrawColor(*rend, 50, 50, 50, 200);
    SDL_RenderClear(*rend);

    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 75, 10, "ALTER-Tank", 200, 100, 100, 255);

    SDL_RenderSetScale(*rend, 2, 2);

    SDL_RenderSetScale(*rend, 2, 2);

    if(mnu.NewGame){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 125 * 2, 125 * 2, 205 * 2, 143 *2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 135, 130, "New Game", 100, 200, 10, 200);
    }
    else{
        stringRGBA(*rend, 135, 130, "New Game", 10, 100, 200, 200);
    }


    if(mnu.LoadStart){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 140*2, 145*2, 190*2, 163*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 150, 150, "Load", 100, 200, 10, 200);
    } else{
        stringRGBA(*rend, 150, 150, "Load", 10, 100, 200, 200);
    }


    SDL_RenderSetScale(*rend, 1, 1);

    SDL_RenderPresent(*rend);
}

void DrawSelectMapMenu(SDL_Renderer** rend, Menu mnu){
    SDL_SetRenderDrawColor(*rend, 50, 50, 50, 200);
    SDL_RenderClear(*rend);
    Map map;
    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 75, 10, "ALTER-Tank", 200, 100, 100, 255);


    SDL_RenderSetScale(*rend, 1, 1);
    if(mnu.promap){
        map = Getpro();
        DrawMap(rend, map.wall, 0);
    }

    if(mnu.simplemap){
        map = Getsimple();
        DrawMap(rend, map.wall, 0);
    }

    filledTrigonRGBA(*rend, 155, 243, 165, 233, 165, 253, 200, 200, 200, 200);
    filledTrigonRGBA(*rend, 525, 243, 515, 233, 515, 253, 200, 200, 200, 200);

    SDL_RenderSetScale(*rend, 1, 1);
    roundedBoxRGBA(*rend, 125 * 2, 245 * 2, 212 * 2, 262 * 2, 10, 0, 0, 50, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, 130, 250, "Select Map", 100, 200, 10, 240);

    SDL_RenderSetScale(*rend, 1, 1);
    SDL_RenderPresent(*rend);
}

void DrawMinMenu(SDL_Renderer** rend, Menu mnu, Tanks T){

    SDL_SetRenderDrawColor(*rend, 50, 50, 50, 200);
    SDL_RenderClear(*rend);
    SDL_RenderSetScale(*rend, 4, 4);

    char* buffer = malloc(sizeof(char) * 50);
    thickLineRGBA(*rend, -10, 160/4, 690, 160/4, 20, 200, 200, 200, 200);
    sprintf(buffer, "%d", T.tank[0].score);
    stringRGBA(*rend, 255/4, 150/4, buffer, T.tank[0].clr.r, T.tank[0].clr.g, T.tank[0].clr.b, 200);
    stringRGBA(*rend, 277/4, 150/4, " - ", 0, 0, 0, 200);
    sprintf(buffer, "%d", T.tank[1].score);
    stringRGBA(*rend, 360/4, 150/4, buffer, T.tank[1].clr.r, T.tank[1].clr.g, T.tank[1].clr.b, 200);
    free(buffer);



    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 75, 10, "ALTER-Tank", 200, 100, 100, 255);

    SDL_RenderSetScale(*rend, 2, 2);

    if(!(mnu.Exit || mnu.SaveGame)){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 130*2, 145*2, 200*2, 162*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 135, 150, " Resume ", 100, 200, 10, 200);
    }
    else{
        stringRGBA(*rend, 135, 150, " Resume ", 10, 100, 200, 200);
    }


    if(mnu.SaveGame){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 142*2, 165*2, 188*2, 182*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 150, 170, "Save", 100, 200, 10, 200);
    } else{
        stringRGBA(*rend, 150, 170, "Save", 10, 100, 200, 200);
    }


    if(mnu.Exit){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 142*2, 185*2, 188*2, 202*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 150, 190, "Exit", 100, 200, 10, 200);
    } else{
        stringRGBA(*rend, 150, 190, "Exit", 10, 100, 200, 200);
    }

    SDL_RenderSetScale(*rend, 1, 1);

    SDL_RenderPresent(*rend);
}

void DrawPopUP(SDL_Renderer** rend, Pop p){

    if(!(p.exist)){ return;}

    filledCircleRGBA(*rend, p.x, p.y, 10, 200, 150, 0, 255);
    thickLineRGBA(*rend, p.x-2, p.y+5, p.x+7-3, p.y+5, 3, 100, 0, 0, 255);
    thickLineRGBA(*rend, p.x-2, p.y-5, p.x-2, p.y+5, 3, 100, 0, 0, 255);
}

void DrawLaser(SDL_Renderer** rend, Tanks* T){
    Tank tnk;
    if(T->tank[0].laser.exist){tnk = T->tank[0];}
    if(T->tank[1].laser.exist){tnk = T->tank[1];}

    if(T->tank[0].laser.exist || T->tank[1].laser.exist) {
        thickLineRGBA(*rend, tnk.laser.x, tnk.laser.y, tnk.laser.Xend, tnk.laser.Yend, 5, 200, 100, 50, 200);
    }
}

void DrawShotenLaser(SDL_Renderer** rend, Tanks*T){
    Tank tnk;
    double x, y;
    double dx;
    double dy;
    if(!(T->tank[0].laser.shoot || T->tank[1].laser.shoot)){ return; }
    if(T->tank[0].laser.shoot){tnk = T->tank[0]; T->tank[0].laser.shoot = 0;}
    if(T->tank[1].laser.shoot){tnk = T->tank[1]; T->tank[1].laser.shoot = 0;}
    x = tnk.x + tnk.Radius * cos(tnk.angle);
    y = tnk.y + tnk.Radius * sin(tnk.angle);


    while  ( (x<600 && y<600) && (x>0 && y>0) && PointDistance(x, y, T->tank[0].x, T->tank[0].y) >= tnk.Radius - 3
                                              && PointDistance(x, y, T->tank[1].x, T->tank[1].y) >= tnk.Radius - 3){
        SDL_RenderPresent(*rend);
        dx = 3*cos(tnk.laser.angle);
        dy = 3*sin(tnk.laser.angle);
        x += dx ;
        y += dy ;
        if(PointDistance(x, y, T->tank[0].x, T->tank[0].y) < tnk.Radius - 3){T->tank[0].exist = 0;T->tank[0].ShootTime=SDL_GetTicks();}
        if(PointDistance(x, y, T->tank[1].x, T->tank[1].y) < tnk.Radius - 3){T->tank[1].exist = 0;T->tank[1].ShootTime=SDL_GetTicks();}
        filledCircleRGBA(*rend, x, y, 3, 100, 0, 0, 200);
        SDL_Delay(3);
    }
}

void DrawEndMenu(SDL_Renderer** rend, Tanks T, Menu mnu, int time){
    SDL_SetRenderDrawColor(*rend, 50, 50, 50, 200);
    SDL_RenderClear(*rend);
    SDL_RenderSetScale(*rend, 4, 4);

    char* buffer = malloc(sizeof(char) * 50);
    thickLineRGBA(*rend, -10, 160/4, 690, 160/4, 20, 200, 200, 200, 200);
    sprintf(buffer, "%d", T.tank[0].score);
    stringRGBA(*rend, 255/4, 150/4, buffer, T.tank[0].clr.r, T.tank[0].clr.g, T.tank[0].clr.b, 200);
    stringRGBA(*rend, 277/4, 150/4, " - ", 0, 0, 0, 200);
    sprintf(buffer, "%d", T.tank[1].score);
    stringRGBA(*rend, 360/4, 150/4, buffer, T.tank[1].clr.r, T.tank[1].clr.g, T.tank[1].clr.b, 200);

    sprintf(buffer, "Game time: %d (s)", (time)/1000);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, 210/2, 500/2, buffer, 0, 0, 0, 200);

    free(buffer);



    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 65, 10, " Game  Over", 200, 100, 100, 255);

    SDL_RenderSetScale(*rend, 2, 2);

    if(mnu.NewGame){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 130*2, 145*2, 200*2, 162*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 135, 150, "New Game", 100, 200, 10, 200);
    }
    else{
        stringRGBA(*rend, 135, 150, "New Game", 10, 100, 200, 200);
    }


    if(mnu.LoadStart){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 103*2, 165*2, 235*2, 182*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 105, 170, "Start saved Game", 100, 200, 10, 200);
    } else{
        stringRGBA(*rend, 105, 170, "Start saved Game", 10, 100, 200, 200);
    }


    if(mnu.Exit){
        SDL_RenderSetScale(*rend, 1, 1);
        roundedBoxRGBA(*rend, 142*2, 185*2, 188*2, 202*2, 10, 0, 0, 50, 255);
        SDL_RenderSetScale(*rend, 2, 2);
        stringRGBA(*rend, 150, 190, "Exit", 100, 200, 10, 200);
    } else{
        stringRGBA(*rend, 150, 190, "Exit", 10, 100, 200, 200);
    }

    SDL_RenderSetScale(*rend, 1, 1);

    SDL_RenderPresent(*rend);
}

void DrawScoreMenu(SDL_Renderer** rend, int score){
    SDL_SetRenderDrawColor(*rend, 50, 50, 50, 200);
    SDL_RenderClear(*rend);
    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 75, 10, "ALTER-Tank", 200, 100, 100, 255);

    char* buffer = malloc(sizeof(char) * 50);
    SDL_RenderSetScale(*rend, 5, 5);
    sprintf(buffer, "%d", score);
    stringRGBA(*rend, 310/5, 300/5, buffer, 200, 200, 200, 200);

    SDL_RenderSetScale(*rend, 1, 1);


    filledTrigonRGBA(*rend, 155, 303, 165, 293, 165, 313, 200, 200, 200, 200);
    filledTrigonRGBA(*rend, 505, 303, 495, 293, 495, 313, 200, 200, 200, 200);

    SDL_RenderSetScale(*rend, 1, 1);
    roundedBoxRGBA(*rend, 110 * 2, 245 * 2, 225 * 2, 262 * 2, 10, 0, 0, 50, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, 120, 250, "Select Score", 100, 200, 10, 240);

    SDL_RenderSetScale(*rend, 1, 1);
    SDL_RenderPresent(*rend);
}

void DrawWelcome(SDL_Renderer** rend, double * agl){
    SDL_SetRenderDrawColor(*rend, 150, 150, 150, 200);
    SDL_RenderClear(*rend);

    SDL_RenderSetScale(*rend, 3, 3);
    stringRGBA(*rend, 90, 10, "WELCOME", 10, 10, 10, 150);
    SDL_RenderSetScale(*rend, 1, 1);



    filledCircleRGBA(*rend, 50, 300, 20, 100, 0, 0, 150);
    filledCircleRGBA(*rend, 50, 300, 20 * 2 / 3, 150, 150, 150, 255);
    filledCircleRGBA(*rend, 50, 300, 20 * 4 / 5, 100, 0, 0, 150);
    thickLineRGBA(*rend, 50, 300, 50 + 20 * cos(3.1415/4) * 1.05, 300 + 20 * sin(3.1415/4) * 1.05,20 * 15/20, 150, 150, 150, 255);
    filledCircleRGBA(*rend, 50, 300, 10, 100, 0, 0, 255);
    thickLineRGBA(*rend, 50, 300, 50 + 20 * cos(3.1415/4), 300 + 20 * sin(3.1415/4), 5, 50, 0, 0, 255);


    filledCircleRGBA(*rend, 630, 300, 20, 0, 0, 100, 150);
    filledCircleRGBA(*rend, 630, 300, 20 * 2 / 3, 150, 150, 150, 255);
    filledCircleRGBA(*rend, 630, 300, 20 * 4 / 5, 0, 0, 100, 150);
    thickLineRGBA(*rend, 630, 300, 630 + 20 * cos(3*3.1415/4) * 1.05, 300 + 20 * sin(3*3.1415/4) * 1.05,20 * 15/20, 150, 150, 150, 255);
    filledCircleRGBA(*rend, 630, 300, 10, 0, 0, 100, 255);
    thickLineRGBA(*rend, 630, 300, 630 + 20 * cos(3*3.1415/4), 300 + 20 * sin(3*3.1415/4), 5, 0, 0, 50, 255);

    int x = 120;
    int y = 300;

    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 100, 40, 40, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "A", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 100, 40, 40, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "S", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    y -=(40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 100, 40, 40, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "W", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+5);y +=(40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 100, 40, 40, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "D", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+20);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 100, 70, 70, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "R", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += 100;
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 70, 70, 100, 200);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "P", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+20);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 70, 70, 100, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "J", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 70, 70, 100, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "K", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    y-=(40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 70, 70, 100, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "I", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x += (40+5);y+=(40+5);
    roundedBoxRGBA(*rend, x, y, x+40, y+40, 10, 70, 70, 100, 255);
    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, (x+13)/2, (y+13)/2, "L", 150, 200, 150, 200);
    SDL_RenderSetScale(*rend, 1, 1);


    SDL_RenderSetScale(*rend, 1.5, 1.5);
    stringRGBA(*rend, 115/1.5, 120/1.5, "Mohammad Sadra Heydari's CE Project 1397", 50, 50, 10, 200);

    SDL_RenderSetScale(*rend, 2, 2);
    stringRGBA(*rend, 240/2, 500/2, "Loading", 20, 20, 1, 200);
    SDL_RenderSetScale(*rend, 1, 1);

    x = 375;
    y = 510;


    thickLineRGBA(*rend, x+10*cos(*agl), y+10*sin(*agl), x+15*cos(*agl), y+15*sin(*agl)                                            , 7, 100, 100, 10, 100);
    thickLineRGBA(*rend, x+10*cos(*agl+1*3.1415/8), y+10*sin(*agl+1*3.1415/8), x+15*cos(*agl+1*3.1415/8), y+15*sin(*agl+1*3.1415/8), 7, 100, 100, 10, 150);
    thickLineRGBA(*rend, x+10*cos(*agl+2*3.1415/8), y+10*sin(*agl+2*3.1415/8), x+15*cos(*agl+2*3.1415/8), y+15*sin(*agl+2*3.1415/8), 7, 100, 100, 10, 200);
    thickLineRGBA(*rend, x+10*cos(*agl+3*3.1415/8), y+10*sin(*agl+3*3.1415/8), x+15*cos(*agl+3*3.1415/8), y+15*sin(*agl+3*3.1415/8), 7, 100, 100, 10, 250);

    *agl += 3.1415/8;

    SDL_Delay(50);

    SDL_RenderSetScale(*rend, 1, 1);
    SDL_RenderPresent(*rend);
}

#endif //ALTERTANK_GRAPH_H
