//
// Created by sadra on 12/29/18.
//
#ifndef ALTERTANK_MOVE_H
#define ALTERTANK_MOVE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

double angleplus = 5 * 3.1415 / 180;

void moveTank1(Tank* tank, Escape* esc){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 3;

    if (event[SDL_SCANCODE_UP]) {                        // Move Up;
        if (tank->Permition.Up && sin(tank->angle) > 0) {
            tank->y += speed * sin(tank->angle);
        }
        if (tank->Permition.Down && sin(tank->angle) < 0) {
            tank->y += speed * sin(tank->angle);
        }
        if (tank->Permition.Left && cos(tank->angle) < 0) {
            tank->x += speed * cos(tank->angle);
        }
        if (tank->Permition.Right && cos(tank->angle) > 0) {
            tank->x += speed * cos(tank->angle);
        }
    }

    if (event[SDL_SCANCODE_DOWN]) {                      // Move Down;
        if (tank->Permition.Up && sin(tank->angle) < 0) {
            tank->y -= speed * sin(tank->angle);
        }
        if (tank->Permition.Down && sin(tank->angle) > 0) {
            tank->y -= speed * sin(tank->angle);
        }
        if (tank->Permition.Left && cos(tank->angle) > 0) {
            tank->x -= speed * cos(tank->angle);
        }
        if (tank->Permition.Right && cos(tank->angle) < 0) {
            tank->x -= speed * cos(tank->angle);
        }

    }
    if (event[SDL_SCANCODE_LEFT]) {                      // Turn Left;
        tank->angle -= angleplus;
    }
    if (event[SDL_SCANCODE_RIGHT]) {                     // Turn Right;
        tank->angle += angleplus;
    }
    tank->laser.angle = tank->angle;
    tank->laser.x = tank->x;
    tank->laser.y = tank->y;
    if (event[SDL_SCANCODE_SPACE]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();

            if(tank->laser.exist){
                tank->laser.Xend = tank->laser.Yend = 600;
                tank->laser.shoot = 1;
                tank->laser.exist = 0;
                return;
            }


            for (int i = 0; i < 5; ++i) {

                if (tank->bullet[i].haveShoten == 0) {
                    tank->bullet[i].LastShot = SDL_GetTicks();
                    tank->bullet[i].haveShoten = 1;
                    tank->bullet[i].alphax = tank->bullet[i].alphay = 1;
                    tank->bullet[i].x = tank->x + tank->Radius * cos(tank->angle) * 5 / 6;
                    tank->bullet[i].y = tank->y + tank->Radius * sin(tank->angle) * 5 / 6;
                    tank->bullet[i].angle = tank->angle;
                    break;
                }
            }
        }

    }

    if (event[SDL_SCANCODE_ESCAPE]) {

        SDL_Delay(200);
            esc->time = SDL_GetTicks();
            esc->exist = 1 - esc->exist;

    }
}

void moveTank2(Tank* tank, Escape* esc){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 3;

    if (event[SDL_SCANCODE_W]) {                        // Move Up;
        if (tank->Permition.Up && sin(tank->angle) > 0) {
            tank->y += speed * sin(tank->angle);
        }
        if (tank->Permition.Down && sin(tank->angle) < 0) {
            tank->y += speed * sin(tank->angle);
        }
        if (tank->Permition.Left && cos(tank->angle) < 0) {
            tank->x += speed * cos(tank->angle);
        }
        if (tank->Permition.Right && cos(tank->angle) > 0) {
            tank->x += speed * cos(tank->angle);
        }
    }

    if (event[SDL_SCANCODE_S]) {                      // Move Down;
        if (tank->Permition.Up && sin(tank->angle) < 0) {
            tank->y -= speed * sin(tank->angle);
        }
        if (tank->Permition.Down && sin(tank->angle) > 0) {
            tank->y -= speed * sin(tank->angle);
        }
        if (tank->Permition.Left && cos(tank->angle) > 0) {
            tank->x -= speed * cos(tank->angle);
        }
        if (tank->Permition.Right && cos(tank->angle) < 0) {
            tank->x -= speed * cos(tank->angle);
        }

    }
    if (event[SDL_SCANCODE_A]) {                      // Turn Left;
        tank->angle -= angleplus;
    }
    if (event[SDL_SCANCODE_D]) {                     // Turn Right;
        tank->angle += angleplus;
    }
    tank->laser.angle = tank->angle;
    tank->laser.x = tank->x;
    tank->laser.y = tank->y;

    if (event[SDL_SCANCODE_5]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();

            if(tank->laser.exist){
                tank->laser.Xend = tank->laser.Yend = 600;
                tank->laser.shoot = 1;
                tank->laser.exist = 0;
                return;
            }

            for (int i = 0; i < 5; ++i) {

                if (tank->bullet[i].haveShoten == 0) {
                    tank->bullet[i].LastShot = SDL_GetTicks();
                    tank->bullet[i].haveShoten = 1;
                    tank->bullet[i].alphax = tank->bullet[i].alphay = 1;
                    tank->bullet[i].x = tank->x + tank->Radius * cos(tank->angle) * 5 / 6;
                    tank->bullet[i].y = tank->y + tank->Radius * sin(tank->angle) * 5 / 6;
                    tank->bullet[i].angle = tank->angle;
                    break;
                }
            }
        }
        if (event[SDL_SCANCODE_ESCAPE]) {

            SDL_Delay(200);
            esc->time = SDL_GetTicks();
            esc->exist = 1 - esc->exist;

        }
    }

}

#endif //ALTERTANK_MOVE_H
