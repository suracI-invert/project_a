#include"texture.h"


//texture class
Texture::Texture(const char* path) {
    SDL_Surface* loadedSurface=IMG_Load(path);
    if(!loadedSurface) throw std::runtime_error{"Failed to load image: " + std::string{path} + "\n" + "Error: " + IMG_GetError()};
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    
    qTexture=SDL_CreateTextureFromSurface(game::renderer, loadedSurface);
    if(!qTexture) throw std::runtime_error{"Failed to create texture from loaded image: " + std::string{path} + "\n" "Error: " + SDL_GetError()};
    
    qWidth=loadedSurface->w;
    qHeight=loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);

    std::cout<<"texture loaded"<<std::endl;

}

#ifdef SDL_TTF_MAJOR_VERSION
Texture::Texture(const char* text, SDL_Color color ) {
    SDL_Surface* textSurface=TTF_RenderText_Solid(gFont, text.c_str(), color);
    if(!textSurface) throw std::runtime_error{"Failed to load text: " + text + "; " + "Error: " + TTF_GetError()};

    qTexture=SDL_CreateTextureFromSurface(render, textSurface);
    if(!qTexture) throw std::runtime_error{"Failed to create texture from loaded text:  " + text + "; " + "Error: " + SDL_GetError()};
    qWidth=textSurface->w;
    qHeight=textSurface->h;

    SDL_FreeSurface(textSurface);
}
#endif

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(qTexture, red, green, blue);
}

void Texture::renderOut(SDL_Rect* src, SDL_Rect* dest) {
    
    SDL_RenderCopy(game::renderer, qTexture, src, dest);
}

void Texture::renderOut(SDL_Rect* src, SDL_Rect* dest, const double& angle, SDL_Point* center) {
    
    SDL_RenderCopyEx(game::renderer, qTexture, src, dest, angle, center, SDL_FLIP_NONE);
}

int Texture::getWidth() const {
    return qWidth;
}

int Texture::getHeight() const {
    return qHeight;
}

Texture::~Texture() {
    if(qTexture==nullptr) SDL_DestroyTexture(qTexture);
    std::cout<<"free texture"<<std::endl;
}


SDL_Texture* Texture::getTexture() const {return qTexture;}


