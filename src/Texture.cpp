// #include"Texture.hpp"
// #include"game.hpp"

// Texture::Texture() {}
// Texture::~Texture() {
//     textures.clear();
// }

// void Texture::add_texture(const std::string& id, const char* path) {
//     SDL_Surface* loadedSurface = IMG_Load(path);
//     if (!loadedSurface) throw std::runtime_error("Failed to load image: " + std::string(path) + "\nError: " + IMG_GetError());
//     SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

//     SDL_Texture* texture = SDL_CreateTextureFromSurface(game::renderer, loadedSurface);
//     if (!texture) throw std::runtime_error("Failed to load image: " + std::string(path) + "\nError: " + IMG_GetError());

//     SDL_FreeSurface(loadedSurface);
//     textures.emplace(id, texture);
// }

// SDL_Texture* Texture::get_texture(const std::string& id) const {
//     return textures.at(id).get();
// }