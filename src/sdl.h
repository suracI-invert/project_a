#ifndef _SDL_H
#define _SDL_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

class sdl{
	private:
		static auto _swap(sdl& a, sdl& b);

		bool _own=false;

	public:
		sdl();

		sdl(sdl&& other);

		~sdl();

		auto operator=(sdl&& other)->sdl&;

		sdl(sdl const&)=delete;
		auto operator=(sdl const&)->sdl& =delete;
};

class img{
    private:   
        static auto _swap(img& a, img& b);

        bool _own=false;
    
    public:
        img();

        img(img&& other);

        ~img();

        auto operator=(img&& other)->img&;

        img(img const&)=delete;
        auto operator=(img const&)->img& =delete;
};

class mus{
    private:
        static auto _swap(mus& a, mus& b);

        bool _own=false;

    public:
        mus();

        mus(mus&& other);

        ~mus();

        auto operator=(mus&& other)->mus&;

        mus(mus const&)=delete;
        auto operator=(mus const&)->mus& =delete;
};


#endif
