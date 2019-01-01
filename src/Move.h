//
// Created by sadra on 12/29/18.
//
#ifndef ALTERTANK_MOVE_H
#define ALTERTANK_MOVE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void moveTank1(Tank* tank){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 5;

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
        tank->angle -= 264;
    }
    if (event[SDL_SCANCODE_RIGHT]) {                     // Turn Right;
        tank->angle += 264;
    }

    if (event[SDL_SCANCODE_SPACE]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();
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

}

void moveTank2(Tank* tank){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 5;

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
        tank->angle -= 264;
    }
    if (event[SDL_SCANCODE_D]) {                     // Turn Right;
        tank->angle += 264;
    }

    if (event[SDL_SCANCODE_5]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();
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

}

void moveTank3(Tank* tank){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 5;

    if (event[SDL_SCANCODE_G]) {                        // Move Up;
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

    if (event[SDL_SCANCODE_B]) {                      // Move Down;
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
    if (event[SDL_SCANCODE_V]) {                      // Turn Left;
        tank->angle -= 264;
    }
    if (event[SDL_SCANCODE_N]) {                     // Turn Right;
        tank->angle += 264;
    }

    if (event[SDL_SCANCODE_M]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();
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

}

void moveTank4(Tank* tank){

    const Uint8 *event = SDL_GetKeyboardState(NULL);
    const int speed = 5;

    if (event[SDL_SCANCODE_I]) {                        // Move Up;
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

    if (event[SDL_SCANCODE_K]) {                      // Move Down;
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
    if (event[SDL_SCANCODE_J]) {                      // Turn Left;
        tank->angle -= 264;
    }
    if (event[SDL_SCANCODE_L]) {                     // Turn Right;
        tank->angle += 264;
    }

    if (event[SDL_SCANCODE_P]) {

        if ((SDL_GetTicks() - tank->lastTime) > 200) {

            tank->lastTime = SDL_GetTicks();
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

}

#endif //ALTERTANK_MOVE_H
