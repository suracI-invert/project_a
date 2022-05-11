#include"input.h"

input::input() {
    quit_=false;
}

bool input::quit() const {return quit_;}
void input::update() {
    key_state=SDL_GetKeyboardState(nullptr);
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:  
                quit_=true;
            case SDL_KEY
        }
    }

}