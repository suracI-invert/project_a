#include"texture.h"

//texture class
Texture::Texture(const std::string& path, SDL_Renderer* render) {
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(!loadedSurface) throw std::runtime_error{"Failed to load image: " + path + "; " + "Error: " + IMG_GetError()};
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    
    qTexture=SDL_CreateTextureFromSurface(render, loadedSurface);
    if(!qTexture) throw std::runtime_error{"Failed to create texture from loaded image: " + path + "; " "Error: " + SDL_GetError()};
    
    qWidth=loadedSurface->w;
    qHeight=loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);
}

#ifdef SDL_TTF_MAJOR_VERSION
Texture::Texture(std::string const& text, SDL_Color color ) {
    SDL_Surface* textSurface=TTF_RenderText_Solid(gFont, text.c_str(), color);
    if(!textSurface) throw std::runtime_error{"Failed to load text: " + text + "; " + "Error: " + TTF_GetError()};

    qTexture=SDL_CreateTextureFromSurface(render, textSurface);
    if(!qTexture) throw std::runtime_error{"Failed to create texture from loaded text:  " + text + "; " + "Error: " + SDL_GetError()};
    qWidth=textSurface->w;
    qHeight=textSurface->h;

    SDL_FreeSurface(textSurface);
}
#endif

void Texture::renderOut(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect renderQuad={x, y, qWidth, qHeight};
    SDL_RenderCopy(renderer, qTexture, nullptr, &renderQuad);
}

int Texture::getWidth() {
    return qWidth;
}

int Texture::getHeight() {
    return qHeight;
}

Texture::~Texture() {
    if(qTexture==nullptr) SDL_DestroyTexture(qTexture);
}


SDL_Texture* Texture::getTexture() {return qTexture;}


