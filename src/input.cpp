#include"input.h"

input::input() {
    quit_=false;
}

bool input::quit() const {return quit_;}
void input::update() {
    
    while(SDL_PollEvent(&e)) {
        if(e.type==SDL_QUIT) quit_=true;

        if(e.type==SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_w:

                case SDLK_a:

                case SDLK_s:

                case SDLK_d:

                default:
                    break;
            }

        }

        if(e.type==SDL_KEYUP) {
            switch(e.key.keysym.sym) {
                case SDLK_w:

                case SDLK_a:

                case SDLK_s:

                case SDLK_d:

                default:
                    break;
            }
        }

    }

}