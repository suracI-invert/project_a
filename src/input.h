#ifndef _INPUT_H
#define _INPUT_H

#include<SDL.h>

class input{
    private:
        bool quit_;
        SDL_Event e;
        
    public:
        input();
        bool quit() const;
        void update();
        

};

#endif