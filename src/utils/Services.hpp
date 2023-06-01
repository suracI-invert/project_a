#pragma once

#include"Texture.hpp"
#include"Shader.hpp"

#include<map>
#include<memory>

/**
 * Static singleton class that hols services like shaders, textures, audio,...
 * 
 * No constructor or object instatiated, all static.
*/
class Services {
    private:
        Services() {}
    public:
        static std::map<std::string, std::shared_ptr<Shader>> Shaders;
        static std::map<std::string, std::shared_ptr<Texture>> Textures;

        /**
         * Load Shader from shader files
         * compile the shader and link it to a program behind Shader Object
         * 
         * 
         * 
         * @param vShaderFile path to vertex shader file
         * @param fShaderFile path to fragment shader file
         * @param name name of the Shader Object, used for accessing
         * 
         * @return a Shader Object
        */
        static Shader* loadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

        /**
         * Get Shader Object through its name
         * 
         * @param name name of the Shader Object
         * 
         * @return Shader Object
        */
        static Shader* getShader(const std::string& name);

        /**
         * Release the Shader Object id-ed by its name, which means also delete the program behind it.
         * If name is not provided (default value), then all shader programs will be released
         * 
         * @param name name of the Shader Object to be released, empty as default to release all
        */
        static void clearShaders(const std::string& name = "");

        /**
         * Load texture from a image file, identified through its name.
         * Alpha flag whether the image file has alpha field (png) or not (jpg).
         * 
         * Store info under a Texture Object.
         * 
         * @param path path to the image fle
         * @param alpha flag if the image file has alpha field or not
         * @param name name of the texture, used for accessing
         * 
         * @return a Texture Object
        */
        static Texture* loadTexture(const char* path, bool alpha, std::string name);

        /**
         * Get the Texture Object thorugh its name
         * 
         * @param name name of the Texture Object
         * 
         * @return Shader Object
        */
        static Texture* getTexture(const std::string& name);

        /**
         * Release the texture under the Texture Object id-ed by its name
         * If the name is not provided (default value), then all textures will be released
         * 
         * @param name name of the Texture Object to be released, empty as default to release all
        */
        static void clearTextures(const std::string& name = "");

        static void off();
};