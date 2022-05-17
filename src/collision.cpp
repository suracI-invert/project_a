#include"collision.h"

float calculateDistance(const float& ax, const float& ay, const float& bx, const float& by) {
    float distanceByX=(ax-bx)*(ax-bx);
    float distanceByY=(ay-by)*(ay-by);

    return distanceByX+distanceByY;
}

bool collisionCheck(const circle& a, const circle& b) {
    float totalRadiusSquare=a.r + b.r;
    totalRadiusSquare*=totalRadiusSquare;
    if(calculateDistance(a.x, a.y, b.x, b.y)<=totalRadiusSquare) return true;
    return false;
}



int withinBoundary(SDL_Rect& boundaryMark)  {
    if(boundaryMark.x<0) return left;
    if(boundaryMark.x>game::w) return right;
    if(boundaryMark.y<0) return top;
    if(boundaryMark.y>game::h) return down;
    return inside;
}