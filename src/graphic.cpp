#include"graphic.h"
#include<vector>

void render_frame(SDL_Renderer* render, Texture* texture, int x, int y) {
    texture->renderOut(render, x, y);
}