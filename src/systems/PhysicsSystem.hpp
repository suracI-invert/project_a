#pragma once

#include"ecs.hpp"

class PhysicsSystem : public System {
    public:
        void init();
        void update(float dt);
};


