#include"game.h"
#include"entity.h"
#include"component.h"

manager m;

entity& player=m.addEntity();
SDL_Renderer* game::renderer=nullptr;

game::game(const char* title, int x, int y, int w, int h, bool fullscreen) {
    isRunning=true;
    std::cout<<"runinng \n";

    auto const sdl_result=SDL_Init(SDL_INIT_EVERYTHING);
	if(sdl_result!=0) throw std::runtime_error{std::string{"Unable to init sdl: "}+SDL_GetError()};

    auto const img_flags=IMG_INIT_JPG|IMG_INIT_PNG;
    auto const img_result=IMG_Init(img_flags)&img_flags;
    if(img_result!=img_flags) throw std::runtime_error{std::string{"Unable to init sdl_image: "}+IMG_GetError()};

    auto const mix_flags=MIX_INIT_MP3;
    auto const mix_result=Mix_Init(mix_flags)&mix_flags;
    auto const openAudio=Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    if(mix_result!=mix_flags || openAudio<0) throw std::runtime_error{std::string{"Unable init sdl_mus: "}+Mix_GetError()};

    int window_flag=SDL_WINDOW_SHOWN;
    if(fullscreen) {window_flag=SDL_WINDOW_FULLSCREEN;}

    window=SDL_CreateWindow(title, x, y, w, h, window_flag);
    if(!window) throw std::runtime_error{std::string{"Unable create window: "}+SDL_GetError()};
    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) throw std::runtime_error{std::string{"Unable create renderer: "}+SDL_GetError()};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


    player.addComponent<pos>(1280/2, 720/2);
    player.addComponent<sprite>("build/img/main.png");
    
}
game::~game() {
    if(!isRunning) {
        std::cout<<"end game \n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

void game::handleInput() {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
    }
}

void game::update() {
    
    m.reset();
    m.update();
}

void game::render() {
    std::cout<<"render \n";
    SDL_RenderClear(renderer);
    
    
    m.draw();
    std::cout<<player.getComponent<pos>().x<<" ";
    std::cout<<player.getComponent<pos>().y<<std::endl;
    SDL_RenderPresent(renderer);
}

bool game::running() const {return isRunning;}


