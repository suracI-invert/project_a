#include"sdl.h"

//sdl
auto sdl::_swap(sdl& a, sdl& b) {
    std::swap(a._own, b._own);
}

sdl::sdl() {
    auto const result=SDL_Init(SDL_INIT_EVERYTHING);
	if(result!=0) throw std::runtime_error{std::string{"Unable to init sdl: "}+SDL_GetError()};
}

sdl::sdl(sdl&& other) {
    _swap(*this, other);
}

auto sdl::operator=(sdl&& other)->sdl& {
    _swap(*this, other);
	return *this;
}

sdl::~sdl() {
    if(_own) SDL_Quit();
}

//sdl_image
auto img::_swap(img& a, img& b) {
    std::swap(a._own, b._own);
}

img::img() {
    auto const flag=IMG_INIT_JPG|IMG_INIT_PNG;
    auto const result=IMG_Init(flag)&flag;
    if(result!=flag) throw std::runtime_error{std::string{"Unable to init sdl_image: "}+IMG_GetError()};
}

img::img(img&& other) {
    _swap(*this, other);
}

auto img::operator=(img&& other)->img& {
    _swap(*this, other);
    return *this;
}

img::~img() {
    if(_own) IMG_Quit();
}

//sdl_mixer
auto mus::_swap(mus& a, mus& b) {
    std::swap(a._own, b._own);
}

mus::mus() {
    auto const flag=MIX_INIT_MP3;
    auto const result=Mix_Init(flag)&flag;
    auto const openAudio=Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    if(result!=flag || openAudio<0) throw std::runtime_error{std::string{"Unable init sdl_mus: "}+Mix_GetError()};
}

mus::mus(mus&& other) {
    _swap(*this, other);
}

auto mus::operator=(mus&& other)->mus& {
    _swap(*this, other);
    return *this;
}

mus::~mus() {
    if(_own) Mix_Quit();
}
