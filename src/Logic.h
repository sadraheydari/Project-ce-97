//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_LOGIC_H
#define ALTERTANK_LOGIC_H
#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include <math.h>
#include "Graph.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Move.h"
#include "HandleEvent.h"


Map GetMap(Menu mnu){

    Map map;
    FILE* MAP;
    map.dx = map.dy = 0;


    if(mnu.promap){MAP = fopen("pro.txt", "r");}
    else {MAP = fopen("simple.txt", "r");}

    fscanf(MAP, "%d", &map.wall.n);
    for (int i = 0; i < map.wall.n ; ++i) {
        fscanf(MAP,"%d %d %d %d", &map.wall.x1[i], &map.wall.y1[i], &map.wall.x2[i], &map.wall.y2[i]);

        if(map.wall.y2[i] == map.wall.y1[i])
            map.wall.vertical[i] = 0;
        else
            map.wall.vertical[i] = 1;

        if( map.wall.y2[i] > map.dy )
            map.dy = map.wall.y2[i];
        if( map.wall.x2[i] > map.dx )
            map.dx = map.wall.x2[i];
    }


    map.Xscale = 1200 / map.dx;
    map.Yscale = 600  / map.dy;

    if( map.Xscale > map.Yscale )
        map.scale = map.Yscale;
    else
        map.scale = map.Xscale;


    for (int j = 0; j < map.wall.n; ++j) {
        map.wall.x1[j] *= map.scale;
        map.wall.x2[j] *= map.scale;
        map.wall.y1[j] *= map.scale;
        map.wall.y2[j] *= map.scale;
    }


    fclose(MAP);
    return map;
}

Map Getpro(){

    Map map;

    FILE* MAP = fopen("pro.txt", "r");

    fscanf(MAP, "%d", &map.wall.n);
    for (int i = 0; i < map.wall.n ; ++i) {
        fscanf(MAP,"%d %d %d %d", &map.wall.x1[i], &map.wall.y1[i], &map.wall.x2[i], &map.wall.y2[i]);

        if( map.wall.y2[i] > map.dy )
            map.dy = map.wall.y2[i];
        if( map.wall.x2[i] > map.dx )
            map.dx = map.wall.x2[i];
    }

    map.dx = map.dy = 12;
    map.Xscale = 250 / 12;
    map.Yscale = 250 / 12;

    if( map.Xscale > map.Yscale )
        map.scale = map.Yscale;
    else
        map.scale = map.Xscale;


    for (int j = 0; j < map.wall.n; ++j) {
        map.wall.x1[j] = map.wall.x1[j]*map.scale + 215;
        map.wall.x2[j] = map.wall.x2[j]*map.scale + 215;
        map.wall.y1[j] = map.wall.y1[j]*map.scale + 175;
        map.wall.y2[j] = map.wall.y2[j]*map.scale + 175;
    }


    fclose(MAP);
    return map;
}

Map Getsimple(){

    Map map;



    FILE* MAP = fopen("simple.txt", "r");

    fscanf(MAP, "%d", &map.wall.n);
    for (int i = 0; i < map.wall.n ; ++i) {
        fscanf(MAP,"%d %d %d %d", &map.wall.x1[i], &map.wall.y1[i], &map.wall.x2[i], &map.wall.y2[i]);

        if(map.wall.y2[i] == map.wall.y1[i])
            map.wall.vertical[i] = 0;
        else
            map.wall.vertical[i] = 1;

        if( map.wall.y2[i] > map.dy )
            map.dy = map.wall.y2[i];
        if( map.wall.x2[i] > map.dx )
            map.dx = map.wall.x2[i];
    }

    map.dx = map.dy = 8;
    map.Xscale = 250 / map.dx;
    map.Yscale = 250  / map.dy;
    map.scale = map.Xscale;


    for (int j = 0; j < map.wall.n; ++j) {
        map.wall.x1[j] = map.wall.x1[j]*map.scale + 215;
        map.wall.x2[j] = map.wall.x2[j]*map.scale + 215;
        map.wall.y1[j] = map.wall.y1[j]*map.scale + 175;
        map.wall.y2[j] = map.wall.y2[j]*map.scale + 175;
    }


    fclose(MAP);
    return map;
}

double LineDistance(double Xcenter, double Ycenter, double x1, double y1, double x2, double y2){
    double m, r;
    m = (y2-y1)*Xcenter - (x2-x1)*Ycenter + (x2*y1) - (y2*x1);
    r = sqrt((m*m)/((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1)));
    return r;
}

double PointDistance(double Xcenter, double Ycenter, double x, double y){
    double r;
    r = sqrt( (Xcenter-x)*(Xcenter-x)  +  (Ycenter-y)*(Ycenter-y) );
    return r;
}

void SetZone(Tank* tank){
    tank->zone.Up    = tank->y + tank->Radius;
    tank->zone.Down  = tank->y - tank->Radius;
    tank->zone.Right = tank->x + tank->Radius;
    tank->zone.Left  = tank->x - tank->Radius;
}

double MinPointDistance (double x, double y, Wall* wall, int wallNo){
    double Distance, D1 = 0, D2 = 0;
    D1 = PointDistance(x, y, wall->x2[wallNo], wall->y2[wallNo]);
    D2 = PointDistance(x, y, wall->x1[wallNo], wall->y1[wallNo] );


    Distance = D1;
    if(D2 < Distance)
        Distance = D2;

    return Distance;
}

void SetPermition(Tanks* T, Wall wall){


    Zone Distance;
    double MinDis;
    for (int j = 0; j < 2; ++j){
        if (T->tank[j].exist){

            T->tank[j].Permition.Up = T->tank[j].Permition.Down = T->tank[j].Permition.Right = T->tank[j].Permition.Left = 1;

            for (int i = 0; i < T->tank[j].NumberWallsTouched ; ++i) {


                Distance.Up = LineDistance(T->tank[j].x, T->tank[j].zone.Up, wall.x1[T->tank[j].touchedWalls[i]], wall.y1[T->tank[j].touchedWalls[i]], wall.x2[T->tank[j].touchedWalls[i]], wall.y2[T->tank[j].touchedWalls[i]]);
                Distance.Down = LineDistance(T->tank[j].x, T->tank[j].zone.Down, wall.x1[T->tank[j].touchedWalls[i]], wall.y1[T->tank[j].touchedWalls[i]], wall.x2[T->tank[j].touchedWalls[i]], wall.y2[T->tank[j].touchedWalls[i]]);
                Distance.Left = LineDistance(T->tank[j].zone.Left, T->tank[j].y, wall.x1[T->tank[j].touchedWalls[i]], wall.y1[T->tank[j].touchedWalls[i]], wall.x2[T->tank[j].touchedWalls[i]], wall.y2[T->tank[j].touchedWalls[i]]);
                Distance.Right = LineDistance(T->tank[j].zone.Right, T->tank[j].y, wall.x1[T->tank[j].touchedWalls[i]], wall.y1[T->tank[j].touchedWalls[i]], wall.x2[T->tank[j].touchedWalls[i]], wall.y2[T->tank[j].touchedWalls[i]]);


                MinDis = Distance.Up;
                if (Distance.Down < MinDis)
                    MinDis = Distance.Down;
                if (Distance.Left < MinDis)
                    MinDis = Distance.Left;
                if (Distance.Right < MinDis)
                    MinDis = Distance.Right;



                if (Distance.Up == MinDis)
                    T->tank[j].Permition.Up = 0;
                if (Distance.Down == MinDis)
                    T->tank[j].Permition.Down = 0;
                if (Distance.Left == MinDis)
                    T->tank[j].Permition.Left = 0;
                if (Distance.Right == MinDis)
                    T->tank[j].Permition.Right = 0;

                Distance.Up = MinPointDistance(T->tank[j].x, T->tank[j].zone.Up, &wall, T->tank[j].touchedWalls[i]);
                Distance.Down = MinPointDistance(T->tank[j].x, T->tank[j].zone.Down, &wall, T->tank[j].touchedWalls[i]);
                Distance.Left = MinPointDistance(T->tank[j].zone.Left, T->tank[j].y, &wall, T->tank[j].touchedWalls[i]);
                Distance.Right = MinPointDistance(T->tank[j].zone.Right, T->tank[j].y, &wall, T->tank[j].touchedWalls[i]);


                if(Distance.Up < T->tank[j].Radius || Distance.Down < T->tank[j].Radius){
                    if(Distance.Up < Distance.Down)
                        T->tank[j].Permition.Up = 0;
                    if(Distance.Up > Distance.Down)
                        T->tank[j].Permition.Down = 0;
                }
                if(Distance.Left < T->tank[j].Radius || Distance.Right < T->tank[j].Radius){
                    if(Distance.Right < Distance.Left)
                        T->tank[j].Permition.Right = 0;
                    if(Distance.Right > Distance.Left)
                        T->tank[j].Permition.Left = 0;
                }
            }
        }

    }

}

void TankTouchWall(Tanks* T, Wall wall){
    int inLine, LineDis;

    for (int j = 0; j < 4; ++j) {

        if ( T->tank[j].exist ){

            SetZone(&T->tank[j]);
            T->tank[j].NumberWallsTouched = 0;
            T->tank[j].haveTouchedwall = 0;

            for (int i = 0; i < wall.n; ++i) {
                LineDis = LineDistance(T->tank[j].x, T->tank[j].y, wall.x1[i], wall.y1[i], wall.x2[i], wall.y2[i]) < T->tank[j].Radius;
                inLine = 0;
                if ( LineDis ){
                    if ( wall.vertical[i] == 1 ){
                        inLine = (T->tank[j].zone.Up > wall.y1[i]) && (T->tank[j].zone.Down < wall.y2[i]);
                    } else if( wall.vertical[i] == 0){
                        inLine = (T->tank[j].zone.Right > wall.x1[i]) && (T->tank[j].zone.Left < wall.x2[i]);
                    }
                    if ( inLine ){
                        T->tank[j].haveTouchedwall = 1;
                        T->tank[j].touchedWalls[T->tank[j].NumberWallsTouched] = i;
                        T->tank[j].NumberWallsTouched ++;
                    }
                }

            }
        }
    }



}

void BulletTouchWall(Tanks* T, Wall wall){
    int LineDis, inLine;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < wall.n; ++k) {
                LineDis = LineDistance(T->tank[i].bullet[j].x, T->tank[i].bullet[j].y,
                                        wall.x1[k], wall.y1[k],
                                        wall.x2[k], wall.y2[k]) <= 3 ;
                inLine = (T->tank[i].bullet[j].x > wall.x1[k] && T->tank[i].bullet[j].x < wall.x2[k]) ||
                         (T->tank[i].bullet[j].y > wall.y1[k] && T->tank[i].bullet[j].y < wall.y2[k]);

                if( LineDis && inLine ){
                    if (wall.vertical[k]){
                        T->tank[i].bullet[j].alphax *= -1;
                    } else{
                        T->tank[i].bullet[j].alphay *= -1;
                    }
                }

            }
        }
    }

}

void BulletTouchTank(Tanks* T){
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 5; ++i) {
            for (int k = 0; k < 4; ++k) {
                if (T->tank[k].exist){

                    if (T->tank[j].bullet[i].haveShoten) {
                        if (PointDistance(T->tank[k].x, T->tank[k].y, T->tank[j].bullet[i].x, T->tank[j].bullet[i].y) < (T->tank[k].Radius * 7 / 8)) {
                            T->tank[k].exist = 0;
                            T->tank[k].ShootTime = SDL_GetTicks();
                            T->tank[j].bullet[i].haveShoten = 0;
                            T->tank[k].x = T->tank[k].y = -100;
                        }
                    }
                }
            }
        }
    }
}

void RefreshGame(Tanks* T, Map map){
    unsigned long long int time = !(T->tank[1].exist) * T->tank[1].ShootTime + !(T->tank[0].exist) * T->tank[0].ShootTime;
    int refreshtime = 3000;

    if( !(T->tank[0].exist && T->tank[1].exist) && SDL_GetTicks()-(time) > refreshtime){

        T->tank[0].score += T->tank[0].exist;
        T->tank[1].score += T->tank[1].exist;

        for (int k = 0; k < T->Number; ++k) {
            T->tank[k].exist = 1;
            T->tank[k].ShootTime = 0;
            T->tank[k].laser.exist = 0;
            T->tank[k].haveTouchedwall = 1;
            for (int i = 0; i < 5; ++i) {
                T->tank[k].bullet[i].haveShoten = 0;
            }
            while (T->tank[k].haveTouchedwall) {
                T->tank[k].x = rand() % (600);
                T->tank[k].y = rand() % (600);
                T->tank[k].angle = rand() % 57;
                TankTouchWall(T, map.wall);
            }

         }
    }
}

void SaveGame(Tanks T, Menu mnu, int score, int time){
    FILE* sve = fopen("Data.txt", "w");
    if(mnu.simplemap){fprintf(sve, "sim\n");}
    else if(mnu.promap){fprintf(sve, "pro\n");}
    fprintf(sve, "%d %d %f %f %f\n", T.tank[0].exist, T.tank[0].Radius, T.tank[0].x, T.tank[0].y, T.tank[0].angle);
    fprintf(sve, "%d %d %f %f %f\n", T.tank[1].exist, T.tank[1].Radius, T.tank[1].x, T.tank[1].y, T.tank[1].angle);
    fprintf(sve, "%d\n%d\n", T.tank[0].score, T.tank[1].score);
    fprintf(sve, "%d\n", score);
    fprintf(sve, "%d\n", time);
    fclose(sve);
}

void LoadGame(Tanks* T, Menu* mnu, int* score, int* time){
    char name[10];

    FILE* lod = fopen("Data.txt", "r");
    fscanf(lod, "%s", name);
    if(name[0] == 's'){mnu->simplemap = 1;mnu->promap= 0;}
    else{mnu->simplemap = 0;mnu->promap= 1;}
    fscanf(lod, "%d %d %lf %lf %lf", &(T->tank[0].exist), &(T->tank[0].Radius), &(T->tank[0].x), &(T->tank[0].y), &(T->tank[0].angle));
    fscanf(lod, "%d %d %lf %lf %lf", &(T->tank[1].exist), &(T->tank[1].Radius), &(T->tank[1].x), &(T->tank[1].y), &(T->tank[1].angle));
    fscanf(lod, "%d", &(T->tank[0].score));
    fscanf(lod, "%d", &(T->tank[1].score));
    fscanf(lod, "%d", score);
    fscanf(lod, "%d", time);
}

void NewGame(Tanks* T, Map map){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            T->tank[i].bullet[j].haveShoten = 0;
            T->tank[i].bullet[i].alphax = 1;
            T->tank[i].bullet[i].alphay = 1;
        }
        T->tank[i].exist = 0;
        T->tank[i].Radius = 20;
        T->tank[i].x = T->tank[i].y = -50;
    }

    for (int k = 0; k < T->Number; ++k) {
        T->tank[k].exist = 1;
        T->tank[k].ShootTime = 0;
        T->tank[k].score = 0;
        T->tank[k].haveTouchedwall = 1;
        while (T->tank[k].haveTouchedwall){
            T->tank[k].x = rand() % (map.dx * map.scale);
            T->tank[k].y = rand() % (map.dy * map.scale);
            T->tank[k].angle = rand() % 57;
            TankTouchWall(T, map.wall);
        }
    }
}

void SetPopUp(Pop* p, Wall wall){
    int condition = 0;

    while (!condition){
        p->x = rand() % 600;
        p->y = rand() % 600;
        for (int i = 0; i < wall.n; ++i) {
            if(LineDistance(p->x, p->y, wall.x1[i], wall.y1[i], wall.x2[i], wall.y2[i]) < 15)
                condition++;
        }
        if (condition > 0){ condition = 0;}
        else { return;}
    }
}

void TankEatPopUP(Pop* p, Tanks* T){
    if(!(p->exist)){
        if(T->tank[0].laser.exist && SDL_GetTicks() - T->tank[0].laser.time > 5000){
            T->tank[0].laser.exist = 0;
        }
        if(T->tank[1].laser.exist && SDL_GetTicks() - T->tank[1].laser.time > 5000){
            T->tank[1].laser.exist = 0;
        }
        return;
    }

    T->tank[0].laser.exist = 0;
    T->tank[1].laser.exist = 0;
    if(PointDistance(T->tank[0].x, T->tank[0].y, p->x, p->y) < (T->tank[0].Radius + 10)){
        T->tank[0].laser.exist = 1;
        T->tank[0].laser.time = SDL_GetTicks();
        p->exist = 0;
        p->time = SDL_GetTicks() ;
    }
    if(PointDistance(T->tank[1].x, T->tank[1].y, p->x, p->y) < (T->tank[1].Radius + 10)){
        T->tank[1].laser.exist = 1;
        T->tank[1].laser.time = SDL_GetTicks();
        p->exist = 0;
        p->time = SDL_GetTicks();
    }
}

void LaserTouchWall(Tanks* T, Wall wall){
    Tank tnk;
    int i;
    int step = 2;
    int inLine, LineDis, TankDis;
    if(T->tank[0].laser.exist){tnk = T->tank[0]; i = 0;}
    if(T->tank[1].laser.exist){tnk = T->tank[1]; i = 1;}
    double x = tnk.x;
    double y = tnk.y;
    while (T->tank[1].laser.exist || T->tank[0].laser.exist){
        x += step * cos(tnk.angle);
        y += step * sin(tnk.angle);
        for (int k = 0; k < wall.n; ++k) {
            TankDis = PointDistance(x, y, T->tank[1-i].x, T->tank[1-i].y) < tnk.Radius;
            LineDis = LineDistance(x, y, wall.x1[k], wall.y1[k], wall.x2[k], wall.y2[k]) <= 3 ;
            inLine = (x > wall.x1[k] && x < wall.x2[k]) || (y > wall.y1[k] && y < wall.y2[k]);
            if ((inLine && LineDis) || TankDis ){
                T->tank[i].laser.Xend = x;
                T->tank[i].laser.Yend = y;
                return;
            }
        }
    }
}

#endif //ALTERTANK_LOGIC_H
