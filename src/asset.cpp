#include"asset.h"

asset::asset(manager* m_):m(m_) {}
asset::~asset() {}

void asset::addTexture(const std::string& id, const char* path) {
    textures.emplace(id, std::shared_ptr<Texture> {new Texture{path}});
}

std::shared_ptr<Texture> asset::GetTexture(const std::string& id) const {return textures.at(id);}

void asset::createProjectile(const std::string& id, const float& speed, const vector& fireCoor, const vector& offset, const float& r, const vector& direction, bool hostile) {
    auto& bullet=m->addEntity();
    bullet.addComponent<pos>(fireCoor.x+offset.x, fireCoor.y+offset.y, offset.x, offset.y);
    bullet.addComponent<graphic>(id);
    bullet.addComponent<collision>(r, destroy);
    bullet.addComponent<projectile>(speed, direction);
    if(!hostile) bullet.addGroup(friendlyFire);
    else bullet.addGroup(projectiles);
}