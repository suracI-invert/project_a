#include"collision.h"

float calculateDistance(const float& ax, const float& ay, const float& bx, const float& by) {
    float distanceByX=(ax-bx)*(ax-bx);
    float distanceByY=(ay-by)*(ay-by);

    return distanceByX+distanceByY;
}

bool collisionCheckCC(const circle& a, const circle& b) {
    float totalRadiusSquare=a.r + b.r;
    totalRadiusSquare*=totalRadiusSquare;
    if(calculateDistance(a.x, a.y, b.x, b.y)<=totalRadiusSquare) return true;
    return false;
}

bool collisionCheckCR(const circle& a, const SDL_Rect& b) {
    float closest_x, closest_y;
    if(a.x<b.x) closest_x=b.x;
    else if(a.x>b.x+b.w) closest_x=b.x+b.w;
    else closest_x=a.x;

    if(a.y<b.y) closest_y=b.y;
    else if(a.y>b.y+b.h) closest_y=b.y+b.h;
    else closest_y=a.y;

    if(calculateDistance(a.x, a.y, closest_x, closest_y)<a.r*a.r) return true;
    return false;
}


int withinBoundary(const SDL_Rect& boundaryMark)  {
    if(boundaryMark.x<=0) return left;
    if(boundaryMark.x+boundaryMark.w>=game::w) return right;
    if(boundaryMark.y<=0) return top;
    if(boundaryMark.y+boundaryMark.h>=game::h) return down;
    return inside;
}