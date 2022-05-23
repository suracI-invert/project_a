#include"game.h"
#include"infotemp.h"





manager* game::m=new manager;

entity& player=game::m->addEntity();


asset* game::assetManager=new asset(game::m);
SDL_Renderer* game::renderer=nullptr;
SDL_Event game::e;
vector* game::playerPos;

int game::w;
int game::h;

game::game(const char* title, int x, int y, int w, int h, bool fullscreen) {
    isRunning=true;
    // std::cout<<"runinng \n";

    srand((unsigned int)time(0));
    
    this->w=w;
    this->h=h;

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
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

    assetManager->addTexture("start", "build/img/start.png");
    assetManager->addTexture("endScreen", "build/img/end_screen.png");
    assetManager->addTexture("live", "build/img/lives.png");

    health=new UI(3, "build/img/lives.png");

    assetManager->addTexture("player", "build/img/main.png");
    assetManager->addTexture("enemy1", "build/img/enemy_1.png");
    assetManager->addTexture("enemy2", "build/img/enemy_2.png");
    assetManager->addTexture("enemy3", "build/img/enemy_3.png");
    assetManager->addTexture("bullet", "build/img/bullet_1.png");
    assetManager->addTexture("friendlyfire", "build/img/friendly_fire.png");
    assetManager->addTexture("hitfx", "build/img/hit_fx.png");
    assetManager->addTexture("destroyfx", "build/img/destroy_fx.png");
    assetManager->addTexture("particle", "build/img/particle.png");

    menu=assetManager->getTexture("start");
    endScreen=assetManager->getTexture("endScreen");
 
    player.addComponent<pos>(1280/2, 720/2, 13, 38);
    player.addComponent<graphic>("player", true);
    player.addComponent<keyboardHandler>();
    player.addComponent<collision>(12, condone);
    player.getComponent<pos>().setSpeed(3);
    player.addComponent<muzzle>(main_char_lv1, 10);
    player.addComponent<state>(3);
    player.addGroup(players);
    
    

    std::cout<<"init done! \n";
}


game::~game() {
    if(!isRunning) {
        // std::cout<<"end game \n";
        delete(m);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

void game::handleInput() {
    SDL_PollEvent(&e);
    switch(e.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
        case SDL_KEYDOWN:
            if(e.key.keysym.sym==SDLK_ESCAPE) isRunning=false;
            if(e.key.keysym.sym==SDLK_BACKSPACE) start=true;
            break;
    }
}

void game::update() {
    if(start) {
        if(m->getGroup(enemies).empty()) {
            int tmpFlag=flag;
            flag=assetManager->spawnWave(tmpFlag);
        }

        if(m->getGroup(players).empty()) {end=true; health->~UI();}
        else {    
            playerPos=&player.getComponent<pos>().center;
            if(player.getComponent<muzzle>().shoot) assetManager->createProjectile("friendlyfire", 7, player.getComponent<pos>().center, vector{13, 13}, 10, player.getComponent<muzzle>().direcion(), false);
            health->update(player.getComponent<state>().hp);
        }

        m->reset();
        m->update();
        
        for(auto& e:m->getGroup(enemies)) {
            if(e->getComponent<muzzle>().shoot && e->getComponent<muzzle>().flag==3) assetManager->createProjectile("bullet", 3, e->getComponent<pos>().center-vector{14, 14}, vector{14, 14}, 12, e->getComponent<muzzle>().direcion(), true);
            else if(e->getComponent<muzzle>().shoot && e->getComponent<muzzle>().flag==4) {
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[0], true);
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[1], true);
            }
            else if(e->getComponent<muzzle>().shoot && e->getComponent<muzzle>().flag==8) {
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[0], true);
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[1], true);
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[2], true);
                assetManager->createProjectile("bullet", 5, e->getComponent<pos>().center-vector{14, 14}, vector{14,14}, 12, e->getComponent<muzzle>().muzzlesDirection[3], true);
            }
        }

    }
}


void game::render() {
    // std::cout<<"render \n";
    SDL_RenderClear(renderer);

    if(!start) {menu->renderOut(nullptr, nullptr);}
    else {
        health->draw();
        for(auto& i:m->getGroup(players)) {i->draw();}
        for(auto& i:m->getGroup(enemies)) {i->draw();}
        for(auto& i:m->getGroup(projectiles)) {i->draw();}
        for(auto& i:m->getGroup(friendlyFire)) {i->draw();}
    }

    if(end) {endScreen->renderOut(nullptr, nullptr);}

    SDL_RenderPresent(renderer);
}

bool game::running() const {return isRunning;}


