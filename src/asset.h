#ifndef _ASSET_H
#define _ASSET_H

#include<map>

#include"entity.h"
#include"texture.h"
#include"game.h"

class Texture;

class asset{
    private:
        manager* m;
        std::map<std::string, std::shared_ptr<Texture>> textures;
    public:
        asset(manager* m_);
        ~asset();

        void addTexture(const std::string& id, const char* path);
        std::shared_ptr<Texture> GetTexture(const std::string& id) const;

        void createProjectile(const std::string& id, const float& speed, const vector& fireCoor, const vector& offset, const float& r, const vector& direction, bool hostile);
};


#endif