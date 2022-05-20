#ifndef _COLLISION_H
#define _COLLISION_H

#include"component.h"
#include"game.h"
#include"obj.h"
#include<SDL.h>

enum boundaryCollision {
    inside,
    top,
    left,
    down,
    right
};


float calculateDistance(const float& ax, const float& ay, const float& bx, const float& by);
bool collisionCheck(const circle& a, const circle& b);
int withinBoundary(const SDL_Rect& boundaryMark);




#endif
