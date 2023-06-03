#include<Shader.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    const char* vShaderCode = readfile(vertexPath).c_str();
    const char* fShaderCode = readfile(fragmentPath).c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    } else {
        std::cout<<"VERTEX COMPILED\n";
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    } else {
        std::cout<<"FRAGMENT COMPILED\n";
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {glUseProgram(id);}

void Shader::setInt(const char* name, int value, bool use) {
    if (use) this->use();
    glUniform1d(glGetUniformLocation(id, name), value);
}
void Shader::setFloat(const char* name, float value, bool use) {
    if (use) this->use();
    glUniform1d(glGetUniformLocation(id, name), value);
}

void Shader::setVec2f(const char* name, float x, float y, bool use) {
    if (use) this->use();
    glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::setVec2f(const char* name, const glm::vec2& value, bool use) {
    if (use) this->use();
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::setVec3f(const char* name, float x, float y, float z, bool use) {
    if (use) this->use();
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::setVec3f(const char* name, const glm::vec3& value, bool use) {
    if (use) this->use();
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::setVec4f(const char* name, float x, float y, float z, float w, bool use) {
    if (use) this->use();
    glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::setVec4f(const char* name, const glm::vec4& value, bool use) {
    if (use) this->use();
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char* name, const glm::mat4& value, bool use) {
    if (use) this->use();
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(value));
}

std::string Shader::readfile(const char* file_path) {
    std::string content;
    std::ifstream fileStream(file_path);

    if (!fileStream.is_open()) {
        std::cerr<<"FAILED TO OPEN: "<<file_path<<std::endl;
        return "";
    }

    std::string line = "";
    std::cout<<"Reading "<<file_path<<"...\n";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + '\n');
    }
    std::cout<<content<<std::endl;
    fileStream.close();
    return content;
}

Shader::~Shader() {
    std::cout<<"Shader deleted\n";
    glDeleteProgram(this->id);
}