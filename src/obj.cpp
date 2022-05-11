#include"obj.h"


//object
object::object(double x, double y, double vx, double vy, int maxHP) {
    x_=x; 
    y_=y;
    hp_=maxHP;
    vx_=vx; vy_=vy;
    
}

double object::x() const {return x_;}
double object::y() const {return y_;}
double object::vx() const {return vx_;}
double object::vy() const {return vy_;}
int object::hp() const{return hp_;}

void object::changeV(double vx, double vy) {
    vx_=vx;
    vy_=vy;
}

void object::move(double vx, double vy) {
    x_+=vx;
    y_+=vy;
} 

void object::changeHP(int delta) {hp_+=delta;}



//heroin
heroin::heroin(double x, double y, double vx, double vy, int maxHP):object(x, y, vx, vy, maxHP) {
    angle_=0;
}

double heroin::angle() const {return angle_;}