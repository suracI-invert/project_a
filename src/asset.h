#ifndef _ASSET_H
#define _ASSET_H

#include<map>

#include"entity.h"
#include"texture.h"
#include"game.h"
#include"infotemp.h"
#include"audio.h"


class Texture;

class asset{
    private:
        manager* m;
        std::map<std::string, std::shared_ptr<Texture>> textures;
        // std::map<std::string, std::shared_ptr<audioFX>> soundEffects;
        // std::map<std::string, std::shared_ptr<music>> musics;
    public:
        asset(manager* m_);
        ~asset();

        void addTexture(const std::string& id, const char* path);
        std::shared_ptr<Texture> getTexture(const std::string& id) const;

        // void addSoundFX(const std::string& id, const char* path);
        // std::shared_ptr<audioFX> getSoundEffect(const std::string& id) const;

        // void addMusic(const std::string& id, const char* path);
        // std::shared_ptr<music> getMusic(const std::string& id) const;

        void createProjectile(const std::string& id, const float& speed, const vector& fireCoor, const vector& offset, const float& r, const vector& direction, bool hostile);
        
        void createEnemies(object& obj);

        int spawnWave(int flag);

        // bool spawnWave(wave& deploy);

        // void createHitfx(vector& position);
};


#endif