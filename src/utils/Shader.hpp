#pragma once

#include<glad/glad.h>

#include<iostream>
#include<fstream>

/**
 * Shader class used to define individual shader program, identified by id
 * 
 * Constructor params:
 * @param vertexPath path to vertex shader file
 * @param fragmentPath path to fragment shader file
*/
class Shader {
    public:
        unsigned int id;    ///< shader program id, OpenGl uses this id to identify shader programs

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        ~Shader();

    private:
        std::string readfile(const char* file_path);
};
