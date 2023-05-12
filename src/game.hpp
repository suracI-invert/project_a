#pragma once

#include<iostream>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

class game {
    private:
    public:
        static SDL_Renderer* renderer;
        static SDL_Event e;
        static SDL_Window* window;

        game(const char* title, int x, int y, int w, int h, bool fullscreen);
        ~game();
};
