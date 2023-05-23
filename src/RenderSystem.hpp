#pragma once

#include"ecs.hpp"
#include"game.hpp"
#include"vec.hpp"

#include"Color.hpp"

void drawCircle(SDL_Renderer* renderer, vec center, float radius, Color color);

class RenderSystem : public System {
    public:
        void init();
        void update(float dt);
};