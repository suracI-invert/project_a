#include"game.hpp"

#include"Color.hpp"
#include"Gravity.hpp"
#include"RigidBody.hpp"
#include"Transform.hpp"

#include"PhysicsSystem.hpp"
#include"RenderSystem.hpp"

#include <chrono>
#include <random>


Manager manager = Manager();

int main(int argc, char** argv) {
    game gameWorld = game{"test", 50, 50, 1280, 720, false};
    manager.init();
    std::cout<<"123";
    manager.RegisterComponent<Gravity>();
    manager.RegisterComponent<Transform>();
    manager.RegisterComponent<RigidBody>();
    manager.RegisterComponent<Color>();
    
    auto physicsSystem = manager.RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        signature.set(manager.GetComponentType<Gravity>());
        signature.set(manager.GetComponentType<Transform>());
        signature.set(manager.GetComponentType<RigidBody>());
        manager.SetSystemSignature<PhysicsSystem>(signature);
    }
    physicsSystem->init();

    auto renderSystem = manager.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(manager.GetComponentType<Transform>());
        signature.set(manager.GetComponentType<Color>());
        manager.SetSystemSignature<RenderSystem>(signature);
    }

    renderSystem->init();

    std::vector<Entity> entities(10);

    std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(0.0f, 1900.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(100.0f, 200.0f);
	std::uniform_int_distribution<uint8_t> randColor(0, 255);

    float scale = randScale(generator);

    for (auto& entity : entities) {
        entity = manager.CreateEntity();
        manager.AddComponent<Gravity>(entity, {.g = 10});
        manager.AddComponent<Transform>(
            entity, 
            {
                .position = vec(randPosition(generator), 0.0f),
                .rotation = 0,
                .scale = vec(scale, scale)
            }
        );
        manager.AddComponent<RigidBody>(
            entity, 
            {
                .velocity = vec(),
                .acceleration = vec()
            }
        );
        manager.AddComponent<Color>(
            entity,
            {
                .r = randColor(generator),
                .g = randColor(generator),
                .b = randColor(generator),
                .a = 0xff
            }
        );
    }

    float dt = 0.0f;

    bool quit = false;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        auto startTime = std::chrono::high_resolution_clock::now();
        physicsSystem->update(dt);
        
        renderSystem->update(dt);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }

    gameWorld.~game();

    return 0;
}