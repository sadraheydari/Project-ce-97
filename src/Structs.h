//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_STRUCTS_H
#define ALTERTANK_STRUCTS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

typedef struct {
    int exist;
    int x;
    int y;
    unsigned long long int time;
}Pop;

typedef struct {
    int r;
    int g;
    int b;
}color;

typedef struct{
    double x;
    double y;
    double angle;
    unsigned long long int LastShot;
    int haveShoten;
    int alphax;
    int alphay;
}Bullet;

typedef struct {
    int exist;
    int x;
    int y;
    double angle;
    int shoot;
    int Xend;
    int Yend;
    unsigned long long int time;
}Laser;


typedef struct {
    double Up, Down, Left, Right;
}Zone;



typedef struct {
    int Up;
    int Down;
    int Left;
    int Right;
}MovePermision;


typedef struct {
    int exist;
    int Radius;
    double x;
    double y;
    double angle;
    color clr;
    Zone zone;
    Bullet bullet[5];
    int NumberWallsTouched;
    int touchedWalls[4];
    int haveTouchedwall;
    MovePermision Permition;
    unsigned long long int lastTime;
    unsigned long long int ShootTime;
    int score;
    Laser laser;
}Tank;


typedef struct {
    Tank tank[4];
    int Number;
}Tanks;


typedef struct {
    int n;
    int x1[100];
    int x2[100];
    int y1[100];
    int y2[100];
    int vertical[100];
}Wall;

typedef struct {
    int Xscale;
    int Yscale;
    int scale;
    int dx;
    int dy;
    Wall wall;
}Map;

typedef struct {
    int exist;
    unsigned long long int time;
}Escape;

typedef struct {
    char maptype[10];
    int LoadStart;
    int NewGame;
    int ForceExit;
    int promap;
    int simplemap;
    int SaveGame;
    int Exit;
}Menu;


#endif //ALTERTANK_STRUCTS_H
