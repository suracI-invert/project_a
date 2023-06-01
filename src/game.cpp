// #include"game.hpp"


// SDL_Renderer* game::renderer = nullptr;
// SDL_Window* game::window = nullptr;

// game::game(const char* title, int x, int y, int w, int h, bool fullscreen) {
//     auto const sdl_result=SDL_Init(SDL_INIT_EVERYTHING);
// 	if(sdl_result!=0) throw std::runtime_error{std::string{"Unable to init sdl: "}+SDL_GetError()};

//     auto const img_flags=IMG_INIT_JPG|IMG_INIT_PNG;
//     auto const img_result=IMG_Init(img_flags)&img_flags;
//     if(img_result!=img_flags) throw std::runtime_error{std::string{"Unable to init sdl_image: "}+IMG_GetError()};

//     auto const mix_flags=MIX_INIT_MP3;
//     auto const mix_result=Mix_Init(mix_flags)&mix_flags;
//     auto const openAudio=Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
//     if(mix_result!=mix_flags || openAudio<0) throw std::runtime_error{std::string{"Unable init sdl_mus: "}+Mix_GetError()};

//     int window_flag=SDL_WINDOW_SHOWN;
//     if(fullscreen) {window_flag=SDL_WINDOW_FULLSCREEN;}

//     window=SDL_CreateWindow(title, x, y, w, h, window_flag);
//     if(!window) throw std::runtime_error{std::string{"Unable create window: "}+SDL_GetError()};
//     renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
//     if(!renderer) throw std::runtime_error{std::string{"Unable create renderer: "}+SDL_GetError()};
//     SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

// }

// game::~game() {
//     if (window) SDL_DestroyWindow(window);
//     if (renderer) SDL_DestroyRenderer(renderer);
//     Mix_CloseAudio();
//     IMG_Quit();
//     SDL_Quit();
// }