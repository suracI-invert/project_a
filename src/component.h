#ifndef _COMPONENT_H
#define _COMPONENT_H

#include"game.h"
#include"texture.h"
#include"entity.h"
#include"collision.h"
#include"obj.h"


class Texture;

class pos:public component{
    private:
        
    public:
        vector position;
        vector velocity;
        
        float acceleration;
        float speed=1;

        pos()=default;

        pos(float x_, float y_);

        void setSpeed(float speed_);
        
        ~pos() override;

        void init() override;
        void update() override;

};


class graphic:public component{
    private:
        pos* position;
        std::unique_ptr<Texture> texture;

        SDL_Rect src, dest;

        bool rotate=false;
        SDL_Point center;
        double angle;
    public:
        int w, h;

        graphic()=default;

        graphic(const char* path);
        graphic(const char* path, SDL_Point center_);
        
        ~graphic() override {}

        void init() override;
        void update() override;
        void draw() override;
};

class keyboardHandler:public component{
    private:
        pos* position;
        
    public:
        static vector mousePos;

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
        bool hostile;
        circle collider;
        SDL_Rect boundaryMark;
        pos* position;

        collision();
        collision(float offset_x, float offset_y, float r, bool hostile, int boundaryFlag=ignore);

        void init() override;
        void update() override;
};

class behavior:public component{
    private:
        pos* position;
        vector dir;
        vector target;
    public:
        behavior(float x=0, float y=0);
        
        void init() override;
        void update() override;
        void draw() override;
};


#endif