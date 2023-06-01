#pragma once

#include<glad/glad.h>
#include<iostream>

/**
 * Texture in 2D format, construct a texture object create and bind a texture to its buffer from a image
 * 
 * Params for constructors:
 * @param path Path to image file
 * @param alpha Image alpha field viability
*/
class Texture {
    public:
        unsigned int id;    ///< id of texture object
        int width, height, channels; ///< width and height and channels of loaded image
        unsigned int internal_format = GL_RGB;    ///< format of texture object
        unsigned int image_format = GL_RGB;  ///< format of loaded image
        unsigned int wrap_s = GL_REPEAT;    ///< wrapping mode on S axis
        unsigned int wrap_t = GL_REPEAT;    ///< wrapping mode on T axis
        unsigned int filter_min = GL_LINEAR;    ///< filter mode if texture > screen pixels
        unsigned int filter_max = GL_LINEAR;    ///< filter mode if texture < screen pixels

        Texture(const char* path, bool alpha);
        ~Texture();
};