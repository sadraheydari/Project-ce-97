//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_STRUCTS_H
#define ALTERTANK_STRUCTS_H

typedef struct {
    int r;
    int g;
    int b;
}color;

typedef struct{
    double x;
    double y;
    int angle;
    unsigned long long int LastShot;
    int haveShoten;
    int alphax;
    int alphay;
}Bullet;


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



#endif //ALTERTANK_STRUCTS_H
