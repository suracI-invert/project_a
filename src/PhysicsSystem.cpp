#include"physicsSystem.hpp"

#include"Transform.hpp"
#include"RigidBody.hpp"
#include"Gravity.hpp"

extern Manager manager;

void PhysicsSystem::init() {};

void PhysicsSystem::update(float dt) {
    for (auto const& entity : entities) {
        auto& rigidBody = manager.GetComponent<RigidBody>(entity);
        auto& transform = manager.GetComponent<Transform>(entity);
        const auto& gravity = manager.GetComponent<Gravity>(entity);

        rigidBody.acceleration = vec(gravity.g, gravity.g);
        transform.position += rigidBody.velocity * dt;
        rigidBody.velocity += rigidBody.acceleration * dt;
    }
}