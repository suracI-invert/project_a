#include"physicsSystem.hpp"

#include"components/Transform.hpp"
#include"components/RigidBody.hpp"
#include"components/Gravity.hpp"

void PhysicsSystem::init() {};

void PhysicsSystem::update(float dt) {
    unsigned int i = 0;
    for (auto const& entity : entities) {
        i++;
        auto& rigidBody = ECS::GetComponent<RigidBody>(entity);
        auto& transform = ECS::GetComponent<Transform>(entity);
        const auto& gravity = ECS::GetComponent<Gravity>(entity);

        if (transform.position.y <= -100.0f) {
            rigidBody.velocity.y = 0.0f;
        }
        rigidBody.acceleration = 0.0f - gravity.g;
        transform.position += rigidBody.velocity * dt;
        rigidBody.velocity.y += rigidBody.acceleration;


        transform.rotation = dt * i;
    }
}