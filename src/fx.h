#ifndef _FX_H
#define _FX_H

#include<SDL.h>

// #include"texture.h"
// #include"obj.h"

class Texture;

// constexpr int TOTAL_PARTICLES=25;

// class particle{
//     private:
//         int x, y;
//         vector velo;
//         int frame;
//         std::shared_ptr<Texture> texture;
//         SDL_Rect dest;
//     public:
//         particle(float x_, float y_);
//         ~particle();
//         void draw();
//         void update();
//         bool dead();
// };

// class particleSystem{
//     private:
//         std::vector<particle*> particles;
//     public:
//         particleSystem(float x, float y);
//         ~particleSystem();
//         bool empty();
//         void draw();

// };

// class hitfx{
//     private:
//         int x, y;
//         std::shared_ptr<Texture> texture;
//         int frame;
//         SDL_Rect dest;
//     public:
        
//         hitfx(float x_, float y_);
//         ~hitfx() {std::cout<<"hitfx delete!\n";}
//         bool end();

//         void draw();
// };

// class deadfx{
//     private:   
//         int x, y;
//         std::shared_ptr<Texture> texture;
//         int frame;
//         SDL_Rect dest;
//     public:
        
//         deadfx(float x_, float y_);
//         ~deadfx() {std::cout<<"deadfx delete\n";}
//         bool end();
//         void draw();
// };

void DrawCircle(int center_x, int center_y, int radius);

class UI{
    private:
        Texture* texture;
        int frame;
        SDL_Rect src, dest;
    public:
        UI();
        UI(int frame_, const char* path);
        ~UI();
        void update(int current);
        void draw();
};

#endif