#ifndef _OBJ_H
#define _OBJ_H

#include"texture.h"
#include<vector>


class object{
    private:
        double x_, y_;
        double vx_, vy_;
        int hp_;
        
    public:
        object(double x, double y, double vx, double vy, int maxHP);
        
        double x() const;
        double y() const;
        int hp() const;
        double vx() const;
        double vy() const;

        virtual void changeV(double vx, double vy);
        virtual void move(double vx, double vy);
        virtual void changeHP(int delta);
        


};

class heroin:public object{
    private:
        double angle_;
    public:
        heroin(double x, double y, double vx, double vy, int maxHP);

        double angle() const;

};

#endif