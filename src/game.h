#ifndef _GAME_H
#define _GAME_H

#include<iostream>
#include<vector>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>


#include"component.h"
#include"entity.h"
#include"obj.h"
#include"asset.h"

enum groupLabels:std::size_t {
    players, 
    enemies,
    projectiles,
    friendlyFire
};


class asset;

class game{
    private:
        bool isRunning;
        SDL_Window* window;
        
    public:
        static asset* assetManager;
        static vector* playerPos;
        static std::vector<circle*> threatColliders;
        static int w;
        static int h;
        static SDL_Event e;
        static SDL_Renderer* renderer;
        game(const char* title, int x, int y, int w, int h, bool fullscreen);
        ~game();
        
        void handleInput();
        void update();
        void render();

        bool running() const;

};

#endif