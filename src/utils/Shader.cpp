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

void Shader::setBool(const std::string &name, bool value) const {glUniform1d(glGetUniformLocation(id, name.c_str()), (int) value);}
void Shader::setInt(const std::string &name, int value) const {glUniform1d(glGetUniformLocation(id, name.c_str()), value);}
void Shader::setFloat(const std::string &name, float value) const {glUniform1d(glGetUniformLocation(id, name.c_str()), value);}

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