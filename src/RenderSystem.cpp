#include"RenderSystem.hpp"

#include"Transform.hpp"

extern Manager manager;

void RenderSystem::init() {

}

void RenderSystem::update(float dt) {
    SDL_RenderClear(game::renderer);
    for (const auto& entity : entities) {
        const auto& transform = manager.GetComponent<Transform>(entity);
        const auto& color = manager.GetComponent<Color>(entity);
        SDL_FRect rect = {.x= transform.position.x, .y= transform.position.y, .w= transform.scale.x, .h= transform.scale.y};
        SDL_SetRenderDrawColor(game::renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRectF(game::renderer, &rect);
        SDL_RenderPresent(game::renderer);
    }
}