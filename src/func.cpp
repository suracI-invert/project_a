
#include"func.h"

void sdl_deleter::operator()(SDL_Window* p) {
    if(p) SDL_DestroyWindow(p);
}

void sdl_deleter::operator()(SDL_Renderer* p) {
    if(p) SDL_DestroyRenderer(p);
}

void sdl_deleter::operator()(Mix_Music* p) {
    if(p) Mix_FreeMusic(p);
}

std::unique_ptr<SDL_Window, sdl_deleter> create_window(char const* title, int x, int y, int w, int h, Uint32 flags) {
    return std::unique_ptr<SDL_Window, sdl_deleter>{
        SDL_CreateWindow(title, x, y, w, h, flags)
    };
}

std::unique_ptr<SDL_Renderer, sdl_deleter> create_renderer(SDL_Window* window, int index, Uint32 flags) {
    return std::unique_ptr<SDL_Renderer, sdl_deleter>{
        SDL_CreateRenderer(window, index, flags)
    };
}

std::unique_ptr<Mix_Music, sdl_deleter> load_music(char const* address) {
    return std::unique_ptr<Mix_Music, sdl_deleter>{
        Mix_LoadMUS(address)
    };
}