#ifndef _GAME_H
#define _GAME_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>


#include"component.h"
#include"entity.h"
#include"obj.h"
#include"asset.h"
#include"fx.h"

// enum gameState{
//     gameIntro,
//     gameEnd,
//     firstWave,
//     secondWave,
//     thirdWave,
//     fourthWave,
//     fifthWave
// };

enum wave{
    firstWave_1,
    firstWave_2,
    secondWave_1,
    secondWave_2,
    thirdWave_1,
    thirdWave_2,
    fourthWave_1,
    fourthWave_2,
    fifthWave_
};


enum groupLabels:std::size_t {
    players, 
    enemies,
    projectiles,
    friendlyFire,
    hitFx
};


class asset;

class game{
    private:
        bool isRunning;
        SDL_Window* window;
        bool start=false;
        bool end=false;
        int flag;
        std::shared_ptr<Texture> menu;
        std::shared_ptr<Texture> endScreen;
    public:
        static manager* m;
        static asset* assetManager;
        static vector* playerPos;
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