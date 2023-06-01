#include"Services.hpp"

std::map<std::string, std::shared_ptr<Texture>> Services::Textures;
std::map<std::string, std::shared_ptr<Shader>> Services::Shaders;

Shader* Services::loadShader(const char* vShaderFile, const char* fShaderFile, std::string name) {
    Shaders.emplace(name, std::shared_ptr<Shader> {new Shader(vShaderFile, fShaderFile)});
    return Shaders.at(name).get();
}

Shader* Services::getShader(const std::string &name) {return Shaders.at(name).get();}

void Services::clearShaders(const std::string& name) {
    if (name.empty()) Shaders.clear();
    else Shaders.erase(name);
}

Texture* Services::loadTexture(const char* path, bool alpha, std::string name) {
    Textures.emplace(name, std::shared_ptr<Texture> {new Texture(path, alpha)});
    return Textures.at(name).get();
}

Texture* Services::getTexture(const std::string& name) {return Textures.at(name).get();}

void Services::clearTextures(const std::string& name) {
    if (name.empty()) Textures.clear();
    else Textures.erase(name);
}