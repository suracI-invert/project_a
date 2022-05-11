#ifndef _FUNC_H
#define _FUNC_H

#include<memory>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

struct sdl_deleter {
    void operator()(SDL_Window* p);
    void operator()(SDL_Renderer* p);
    void operator()(Mix_Music* p);
};

std::unique_ptr<SDL_Window, sdl_deleter> create_window(char const* title, int x, int y, int w, int h, Uint32 flags);
std::unique_ptr<SDL_Renderer, sdl_deleter> create_renderer(SDL_Window* window, int index, Uint32 flags);
std::unique_ptr<Mix_Music, sdl_deleter> load_music(char const* address); 

#endif