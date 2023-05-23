#pragma once

#include"vec.hpp"
#include"ecs.hpp"
#include"game.hpp"

class PhysicsSystem : public System {
    public:
        void init();
        void update(float dt);
};


