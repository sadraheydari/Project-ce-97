//
// Created by sadra on 12/29/18.
//

#ifndef ALTERTANK_LOGIC_H
#define ALTERTANK_LOGIC_H
#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include <math.h>

Map GetMap(){

    Map map;

    map.dx = map.dy = 0;

    scanf("%d", &map.wall.n);
    for (int i = 0; i < map.wall.n ; ++i) {
        scanf("%d %d %d %d", &map.wall.x1[i], &map.wall.y1[i], &map.wall.x2[i], &map.wall.y2[i]);

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

double MinZoneDistance (double x, double y, Wall* wall, int wallNo){
    double Distance, D1 = 0, D2 = 0, D3 = 0;
    D1 = LineDistance(x, y, wall->x1[wallNo], wall->y1[wallNo], wall->x2[wallNo], wall->y2[wallNo]);
    D2 = PointDistance(x, y, wall->x1[wallNo], wall->y1[wallNo] );
    D3 = PointDistance(x, y, wall->x2[wallNo], wall->y2[wallNo]);

    Distance = D1;
    if(D2 < Distance)
        Distance = D2;
    if(D3 < Distance)
        Distance = D3;

    return Distance;
}

void SetPermition(Tanks* T, Wall wall){


    Zone Distance;
    double MinDis;

    for (int j = 0; j < 4; ++j){
        if (T->tank[j].exist){

            T->tank[j].Permition.Up = T->tank[j].Permition.Down = T->tank[j].Permition.Right = T->tank[j].Permition.Left = 1;

            for (int i = 0; i < T->tank[j].NumberWallsTouched ; ++i) {
                Distance.Up = MinZoneDistance(T->tank[j].x, T->tank[j].zone.Up, &wall, T->tank[j].touchedWalls[i]);
                Distance.Down = MinZoneDistance(T->tank[j].x, T->tank[j].zone.Down, &wall, T->tank[j].touchedWalls[i]);
                Distance.Left = MinZoneDistance(T->tank[j].zone.Left, T->tank[j].y, &wall, T->tank[j].touchedWalls[i]);
                Distance.Right = MinZoneDistance(T->tank[j].zone.Right, T->tank[j].y, &wall, T->tank[j].touchedWalls[i]);

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
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 5; ++i) {
            for (int k = 0; k < 4; ++k) {
                if (T->tank[k].exist){

                    if (T->tank[j].bullet[i].haveShoten) {
                        if (PointDistance(T->tank[k].x, T->tank[k].y, T->tank[j].bullet[i].x, T->tank[j].bullet[i].y) < (T->tank[k].Radius * 7 / 8)) {
                            T->tank[k].exist = 0;
                            T->tank[j].bullet[i].haveShoten = 0;
                            T->tank[k].x = T->tank[k].y = -100;
                        }
                    }
                }
            }
        }
    }
}

#endif //ALTERTANK_LOGIC_H
