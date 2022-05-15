#include"game.h"

#include<vector>
#include<string>

const int FPS=144;
const int frameDelay=1000/FPS;

Uint64 frameStart;
Uint64 frameEnd;
int frameTime;

int main(int argc, char** argv) {
    try {
        auto game_=game{"test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, false};
        while(game_.running()) {
            frameStart=SDL_GetTicks64();
            std::cout<<"start frame \n";

            game_.handleInput();
            game_.update();
            game_.render();

            frameTime=SDL_GetTicks64()-frameStart;

            if(frameDelay>frameTime) SDL_Delay(frameDelay-frameTime);
        
            std::cout<<"end frame \n";
        }
    }
    
    catch(std::exception &ex) {
        std::cerr<<ex.what()<<std::endl;
    }
    return 0;
}