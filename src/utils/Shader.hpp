#pragma once

#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        void setInt(const char* name, int value, bool use = false);
        void setFloat(const char* name, float value, bool use = false);
        void setVec2f(const char* name, float x, float y, bool use = false);
        void setVec2f(const char* name, const glm::vec2& value, bool use = false);
        void setVec3f(const char* name, float x, float y, float z, bool use = false);
        void setVec3f(const char* name, const glm::vec3& value, bool use = false);
        void setVec4f(const char* name, float x, float y, float z, float w, bool use = false);
        void setVec4f(const char* name, const glm::vec4& value, bool use = false);
        void setMatrix4(const char* name, const glm::mat4& value, bool use = false);

        ~Shader();

    private:
        std::string readfile(const char* file_path);
};
