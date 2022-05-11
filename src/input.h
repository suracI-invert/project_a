#ifndef _INPUT_H
#define _INPUT_H

#include<SDL.h>

class input{
    private:
        bool quit_;
        SDL_Event e;
        const Uint8* key_state;
    public:
        input();
        bool quit() const;
        void update();
        bool keyDown(int key);

};

#endif