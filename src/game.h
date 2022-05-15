#ifndef _GAME_H
#define _GAME_H

#include<iostream>

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"

#include"entity.h"
#include"component.h"


class game{
    private:
        bool isRunning;
        SDL_Window* window;
        
    public:
        static SDL_Renderer* renderer;
        game(const char* title, int x, int y, int w, int h, bool fullscreen);
        ~game();
        
        void handleInput();
        void update();
        void render();

        bool running() const;

};

#endif