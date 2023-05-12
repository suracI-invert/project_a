#include"ecs.hpp"

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        availEntities.push(entity);
    }
}

Entity EntityManager::create_entity() {
    if (livingEntities >= MAX_ENTITIES) throw std::runtime_error("Too many entities");

    Entity id = availEntities.front();
    availEntities.pop();
    livingEntities++;

    return id;
}

void EntityManager::destroy_entity(Entity entity) {
    if (entity > MAX_ENTITIES) throw std::runtime_error("Entity out of range");

    signatures[entity].reset();
    availEntities.push(entity);
    livingEntities--;
}

void EntityManager::set_signature(Entity entity, Signature signature) {
    if (entity > MAX_ENTITIES) throw std::runtime_error("Entity out of range");

    signatures[entity] = signature;
}

Signature EntityManager::get_sigature(Entity entity) {
    if (entity > MAX_ENTITIES) throw std::runtime_error("Entity out of range");

    return signatures[entity];
}

void ComponentManager::entity_destroyed(Entity entity) {
    for (auto const& pair : component_arrays) {
        auto const& component = pair.second;
        component -> entity_destroyed(entity);
    }
}

void SystemManager::entity_destroyed(Entity entity) {
    for (auto const& pair : systems) {
        auto const& system = pair.second;
        system->entities.erase(entity);
    }
}

void SystemManager::change_entity_signature(Entity entity, Signature signature) {
    for (auto const& pair : systems) {
        auto const& type = pair.first;
        auto const& system = pair.second;
        auto const& system_sign = signatures[type];

        if ((signature & system_sign) == system_sign) {
            system->entities.insert(entity);
        } else {
            system->entities.erase(entity);
        }
    }
}

void Manager::init() {
    C = std::make_unique<ComponentManager>();
    S = std::make_unique<SystemManager>();
    E = std::make_unique<EntityManager>();
}

Entity Manager::create_entity() {
    return E->create_entity();
}

void Manager::destroy_entity(Entity entity) {
    E->destroy_entity(entity);
    C->entity_destroyed(entity);
    S->entity_destroyed(entity);
}