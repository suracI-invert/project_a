#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<iostream>
#include<string>

#include<SDL.h>
#include<SDL_image.h>



class Texture {
    private: 
        SDL_Texture* qTexture=nullptr;
        int qHeight=0;
        int qWidth=0;

    public: 
        
        Texture(const std::string& path, SDL_Renderer* render);

        #ifdef SDL_TTF_MAJOR_VERSION
        Texture(std::string text, SDL_Color);
        #endif

        virtual ~Texture();

        virtual void renderOut(SDL_Renderer* renderer, int x, int y);


        int getWidth();

        int getHeight();

        SDL_Texture* getTexture();
};

#endif