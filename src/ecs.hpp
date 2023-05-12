#pragma once

#include<iostream>
#include<queue>
#include<unordered_map>
#include<bitset>
#include<array>
#include<memory>
#include<set>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 5000;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
    private:
        std::queue<Entity> availEntities;
        std::array<Signature, MAX_ENTITIES> signatures;
        uint32_t livingEntities;
    public:
        EntityManager();
        Entity create_entity();
        void destroy_entity(Entity entity);
        void set_signature(Entity entity, Signature signature);
        Signature get_sigature(Entity entity);
};

class VComponentArray {
    public:
        virtual ~VComponentArray() = default;
        virtual void entity_destroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public VComponentArray {
    private:
        std::array<T, MAX_ENTITIES> component_array;
        std::unordered_map<Entity, size_t> e_to_c;
        std::unordered_map<size_t, Entity> c_to_e;
        size_t size;
    public:
        void insert_component(Entity entity, T component) {
            if (e_to_c.find(entity) != e_to_c.end()) throw std::runtime_error("Component added to same entity more than once");

            size_t new_idx = size;
            e_to_c[entity] = new_idx;
            c_to_e[new_idx] = entity;
            component_array[new_idx] = component;
            size++;
        }

        void remove_component(Entity entity) {
            if (e_to_c.find(entity) == e_to_c.end()) throw std::runtime_error("Removing non-existence component");

            size_t idx_of_remove_entity = e_to_c[entity];
            size_t idx_of_last_element = size - 1;
            component_array[idx_of_remove_entity] = component_array[idx_of_last_element];

            Entity entity_of_last_element = c_to_e[idx_of_last_element];
            e_to_c[entity_of_last_element] = idx_of_remove_entity;
            c_to_e[idx_of_remove_entity] = entity_of_last_element;

            e_to_c.erase(entity);
            c_to_e.erase(idx_of_last_element);

            size--;
        }

        T& get_component(Entity entity) {
            if (e_to_c.find(entity) != e_to_c.end()) throw std::runtime_error("Retrieving non-existence component");

            return component_array[e_to_c[entity]];
        }

        void entity_destroyed(Entity entity) override {
            if (e_to_c.find(entity) != e_to_c.end()) {
                remove_component(entity);
            }
        }
};

class ComponentManager {
    private:
        std::unordered_map<const char*, ComponentType> component_types;
        std::unordered_map<const char*, std::shared_ptr<VComponentArray>> component_arrays;
        ComponentType next_component_type;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            const char* typename = typeid(T).name();

            if (component_types.find(typename) == component_types.end()) throw std::runtime_error("Component not registered before used");

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[typename]);
        }

    public:
        template<typename T>
        void register_component() {
            const char* typename = typeid(T).name();

            if (component_types.find(typename) != component_types.end()) throw std::runtime_error("Registering component type more than once")
        
            component_types.insert({typename, next_component_type});

            component_arrays.insert({typename, std::make_shared<ComponentArray<T>>()});

            next_component_type++;
        }

        template<typename T>
        ComponentType get_component_type() {
            const char* typename = typeid(T).name();

            if (component_types.find(type_name) == component_types.end()) throw std::runtime_error("Component not registered before use");

            return component_types[typename];
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            get_component_array<T>()->insert_component(entity, component);
        }

        template<typename T>
        void remove_component(Entity entity) {
            get_component_array<T>()->remove_component(entity);
        }

        template<typename T>
        T& get_component(Entity entity) {
            return get_component_array<T>()->get_component(entity);
        }

        void entity_destroyed(Entity entity);
};

class System {
    public:
        std::set<Entity> entities;
};

class SystemManager {
    private:
        std::unordered_map<const char*, Signature> signatures;
        std::unordered_map<const char*, std::shared_ptr<System>> systems;
    public:
        template<typename T>
        std::shared_ptr<T> register_system() {
            const char* typename = typeid(T).name();

            if (systems.find(typename) != systems.end()) throw std::runtime_error("Register system more than once");

            auto system = std::make_shared<T>();
            systems.insert({typename, system});
            return system;
        }

        template<typename T>
        void set_signature(Signature signature) {
            const char* typename = typeid(T).name();

            if (systems.find(typename) == systems.end()) throw std::runtime_error("System used before registered");

            signatures.insert({typename, signature});
        }

        void entity_destroyed(Entity entity);
        void change_entity_signature(Entity entity, Signature signature);
};

class Manager {
    private:
        std::unique_ptr<ComponentManager> C;
        std::unique_ptr<EntityManager> E;
        std::unique_ptr<SystemManager> S;
    public:
        void init();
        Entity create_entity();
        void destroy_entity(Entity entity);

        template<typename T>
        void register_component() {
            C->register_component<T>();
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            C->add_component<T>(entity, component);
        }

        template<typename T>
        void remove_component(Entity entity) {
            C->remove_component<T>(entity);

            auto sign = E->get_sigature(entity);
            sign.set(C->get_component_type<T>(), false);
            E->set_signature(entity, sign);
            S->change_entity_signature(entity, sign);
        }

        template<typename T>
        T& get_component(Entity entity) {
            return C->get_component<T>(entity);
        }

        template<typename T>
        ComponentType get_component_type() {
            return C->get_component_type<T>();
        }

        template<typename T>
        std::shared_ptr<T> register_system() {
            return S->register_system<T>();
        }

        template<typename T>
        void set_system_signature(Signature signature) {
            S->set_signature<T>(signature);
        }
};