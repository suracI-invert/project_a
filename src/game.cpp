#include"game.h"

manager m;

int count =0;

entity& player=m.addEntity();
entity& enemy1=m.addEntity();
entity& enemy2=m.addEntity();
entity& enemy3=m.addEntity();

asset* game::assetManager=new asset(&m);
SDL_Renderer* game::renderer=nullptr;
SDL_Event game::e;
vector* game::playerPos;

int game::w;
int game::h;

game::game(const char* title, int x, int y, int w, int h, bool fullscreen) {
    isRunning=true;
    // std::cout<<"runinng \n";

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    assetManager->addTexture("player", "build/img/main.png");
    assetManager->addTexture("enemy1", "build/img/enemy1.png");
    assetManager->addTexture("bullet", "build/img/enemy1_bullet.png");
 

    player.addComponent<pos>(1280/2, 720/2, 13, 38);
    player.addComponent<graphic>("player", true);
    player.addComponent<keyboardHandler>();
    player.addComponent<collision>(12, condone);
    player.getComponent<pos>().setSpeed(1.5);
    player.addComponent<muzzle>(main_char_lv1, 100);
    player.addGroup(players);


    
    enemy1.addComponent<pos>(100, 100, 15, 15);
    enemy1.addComponent<graphic>("enemy1", false);
    enemy1.addComponent<collision>(15);
    enemy1.addComponent<behavior>();
    enemy1.addComponent<muzzle>(enemy_single_muzzle, 50);
    enemy1.getComponent<pos>().setSpeed(0.5);
    enemy1.addGroup(enemies);

    enemy2.addComponent<pos>(200, 100, 15, 15);
    enemy2.addComponent<graphic>("enemy1", false);
    enemy2.addComponent<collision>(15);
    enemy2.addComponent<behavior>();
    enemy2.getComponent<pos>().setSpeed(0.5);
    enemy2.addGroup(enemies);

    enemy3.addComponent<pos>(100, 300, 15, 15);
    enemy3.addComponent<graphic>("enemy1", false);
    enemy3.addComponent<collision>(15);
    enemy3.addComponent<behavior>();
    enemy3.getComponent<pos>().setSpeed(0.5);
    enemy3.addGroup(enemies);

    std::cout<<"init done! \n";
}

game::~game() {
    if(!isRunning) {
        // std::cout<<"end game \n";
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
            if(e.key.keysym.sym==SDLK_ESCAPE)
                isRunning=false;
                break;
    }
}

void game::update() {
    // std::cout<<"update! \n";
    playerPos=&player.getComponent<pos>().position;
    m.reset();
    m.update();
    // std::cout<<"player: \nx:"<<player.getComponent<pos>().position.x<<" y: "<<player.getComponent<pos>().position.x<<"\n";
    if(enemy1.getComponent<muzzle>().shoot) {assetManager->createProjectile("bullet", 2, enemy1.getComponent<pos>().center, vector{5, 5}, 5, enemy1.getComponent<muzzle>().direcion(), true); std::cout<<"enemy fires \n";}
    if(player.getComponent<muzzle>().shoot) assetManager->createProjectile("bullet", 2, player.getComponent<pos>().center, vector{5, 5}, 5, player.getComponent<muzzle>().direcion(), false);
    
    for(auto& e: m.getGroup(enemies)) {
        if(collisionCheck(player.getComponent<collision>().collider, e->getComponent<collision>().collider)) {
            isRunning=false;
            std::cout<<"game end! \n";
        }
    }

    for(auto& e: m.getGroup(projectiles)) {
        if(collisionCheck(player.getComponent<collision>().collider, e->getComponent<collision>().collider)) {
            isRunning=false;
            std::cout<<"game end! \n";
        }
    }

    for(auto& p:m.getGroup(friendlyFire)) {
        for(auto& e:m.getGroup(enemies)) {
            if(collisionCheck(p->getComponent<collision>().collider, e->getComponent<collision>().collider)) {e->destroy(); p->destroy(); std::cout<<"enemy destroyed!\n";}
        }
    }
}


void game::render() {
    // std::cout<<"render \n";
    SDL_RenderClear(renderer);
    
    for(auto& i:m.getGroup(players)) {i->draw();}
    for(auto& i:m.getGroup(projectiles)) {i->draw();}
    for(auto& i:m.getGroup(friendlyFire)) {i->draw();}
    for(auto& i:m.getGroup(enemies)) {i->draw();}
    
    SDL_RenderPresent(renderer);
}

bool game::running() const {return isRunning;}


