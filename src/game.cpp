#include"game.hpp"


ECS manager();

Game::Game(unsigned int width, unsigned int height) : WIDTH(width), HEIGHT(height) {};

Game::~Game() {

}

void Game::init() {
    Services::loadShader("src/shader/vertex.glsl", "src/shader/fragment.glsl", "default");
    Services::loadTexture("build/img/container.jpg", false, "container");
}

void Game::processInput(float dt) {

}

void Game::update(float dt) {

}

void Game::render(float dt, const glm::mat4& view, float fov) {

}