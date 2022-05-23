#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<iostream>
#include<string>
#include<memory>

#include<SDL.h>
#include<SDL_image.h>

#include"game.h"

class Texture {
    private: 
        SDL_Texture* qTexture=nullptr;
        int qHeight=0;
        int qWidth=0;

    

    public: 
        Texture(const char* path);

        #ifdef SDL_TTF_MAJOR_VERSION
        Texture(std::string text, SDL_Color);
        #endif

        ~Texture();

        void renderOut(SDL_Rect* src, SDL_Rect* dest);
        void renderOut(SDL_Rect* src, SDL_Rect* dest, const double& angle, SDL_Point* center);

        void setColor(Uint8 red, Uint8 green, Uint8 blue);


        int getWidth() const;

        int getHeight() const;

        SDL_Texture* getTexture() const;
};

#endif