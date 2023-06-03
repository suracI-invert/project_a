#pragma once

#include<iostream>

#include"ecs.hpp"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"utils/Services.hpp"

class Game {
    public:
        unsigned int WIDTH, HEIGHT;


        Game(unsigned int width, unsigned int height);
        ~Game();

        void init();
        void processInput(float dt);
        void update(float dt);
        void render(float dt, const glm::mat4& view, float fov);
};
