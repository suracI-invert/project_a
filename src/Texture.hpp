// #pragma once

// #include<SDL.h>
// #include<SDL_image.h>

// #include<map>
// #include<iostream>
// #include<memory>

// struct texture_deleter {
//     void operator() (SDL_Texture* t) const {
//         if (t != nullptr) SDL_DestroyTexture(t);
//     }
// };

// class Texture {
//     private:
//         std::map<std::string, std::shared_ptr<SDL_Texture>> textures;

//     public:
//         Texture();
//         ~Texture();

//         void add_texture(const std::string& id, const char* path);

//         SDL_Texture* get_texture(const std::string& id) const;

// };