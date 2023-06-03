#pragma once

#include<glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    float rotation; //in rad
    float scale;
};