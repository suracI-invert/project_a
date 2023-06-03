#include"Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

Texture::Texture(const char* path, bool alpha) {
    if (alpha) {
        this->internal_format = GL_RGBA;
        this->image_format = GL_RGBA;
    }

    unsigned char* data = stbi_load(path, &this->width, &this->height, &this->channels, 0);

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, this->width, this->height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    std::cout<<"Texture released\n";
    glDeleteTextures(1, &this->id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
}