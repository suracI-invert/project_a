#ifndef _COMPONENT_H
#define _COMPONENT_H

#include"game.h"
#include"texture.h"
#include"entity.h"
#include"obj.h"
#include"collision.h"


class Texture;

class pos:public component{
    private:
        
    public:
        vector position;
        vector velocity;

        float speed=1;

        pos()=default;

        pos(float x_, float y_);
        
        ~pos() override;

        void init() override;
        void update() override;

};


class graphic:public component{
    private:
        pos* position;
        std::unique_ptr<Texture> texture;
        SDL_Rect src, dest;
    public:
        int w, h;

        graphic()=default;

        graphic(const char* path);
        
        ~graphic() override {}

        void init() override;
        void update() override;
        void draw() override;
};

class keyboardHandler:public component{
    private:
        pos* position;
    public:
        void init() override;
        
        void update() override;
};

enum boundaryInteractions{
    ignore,
    destroy,
    condone
};

class collision:public component{
    private:    
        float offset_x, offset_y, r;
        int boundaryFlag;
    public:
        circle collider;
        SDL_Rect boundaryMark;
        pos* position;

        collision();
        collision(float offset_x, float offset_y, float r, int boundaryFlag=ignore);

        void init() override;
        void update() override;
};




#endif