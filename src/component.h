#ifndef _COMPONENT_H
#define _COMPONENT_H

#include"entity.h"

class Texture;

class pos:public component{
    public:
        double x;
        double y;

        pos()=default;

        pos(double x_, double y_);
        
        ~pos() override;

        void init() override;
        void setPos(double x_, double y_);
        void update() override;

};

class sprite:public component{
    private:
        pos* position;
        std::unique_ptr<Texture> texture;
        SDL_Rect src, dest;
    public:
        sprite()=default;

        sprite(const char* path);
        
        ~sprite() override;

        void init() override;

        void update() override;

        void draw() override;

};

#endif