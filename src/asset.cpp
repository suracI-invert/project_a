#include"asset.h"


asset::asset(manager* m_):m(m_) {}
asset::~asset() {}

void asset::addTexture(const std::string& id, const char* path) {
    textures.emplace(id, std::shared_ptr<Texture> {new Texture{path}});

}

std::shared_ptr<Texture> asset::getTexture(const std::string& id) const {return textures.at(id);}

// void asset::addSoundFX(const std::string& id, const char* path) {
//     soundEffects.emplace(id, std::shared_ptr<audioFX> {new audioFX{path}});
// }

// std::shared_ptr<audioFX> asset::getSoundEffect(const std::string& id) const {return soundEffects.at(id);}

// void asset::addMusic(const std::string& id, const char* path) {
//     musics.emplace(id, std::shared_ptr<music> {new music{path}});
// }

// std::shared_ptr<music> asset::getMusic(const std::string& id) const {return musics.at(id);}

void asset::createProjectile(const std::string& id, const float& speed, const vector& fireCoor, const vector& offset, const float& r, const vector& direction, bool hostile) {
    auto& bullet=m->addEntity();
    if(!hostile) bullet.addComponent<pos>(fireCoor.x-offset.x, fireCoor.y-offset.y, offset.x, offset.y);
    else bullet.addComponent<pos>(fireCoor.x, fireCoor.y, offset.x, offset.y);
    bullet.addComponent<graphic>(id);
    bullet.addComponent<collision>(r, destroy);
    bullet.addComponent<projectile>(speed, direction);
    if(!hostile) bullet.addGroup(friendlyFire);
    else bullet.addGroup(projectiles);
}

void asset::createEnemies(object& obj) {
    auto& enemy=m->addEntity();
    enemy.addComponent<pos>(obj.position.x, obj.position.y, obj.position.offset_center_x, obj.position.offset_center_y);
    enemy.addComponent<graphic>(obj.graphic.id, obj.graphic.rotate);
    enemy.addComponent<collision>(obj.collision.radius, obj.collision.boundaryFlag);
    enemy.addComponent<state>(obj.state.hp);
    enemy.addComponent<behavior>();
    enemy.addComponent<muzzle>(obj.muzzle.flag, obj.muzzle.cooldown);
    enemy.addGroup(enemies);
}









int asset::spawnWave(int flag) {
    switch(flag) {
        case firstWave_1:
            createEnemies(enemy1_pos1);
            return firstWave_2;
        case firstWave_2:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos4);
            createEnemies(enemy1_pos8);
            return secondWave_1;
        case secondWave_1:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos4);
            createEnemies(enemy1_pos8);
            createEnemies(enemy1_pos9);
            createEnemies(enemy1_pos3);
            return secondWave_2;
        case secondWave_2:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos4);
            createEnemies(enemy1_pos8);
            createEnemies(enemy2_pos2);
            return thirdWave_1;
        case thirdWave_1:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos4);
            createEnemies(enemy1_pos8);
            createEnemies(enemy2_pos3);
            createEnemies(enemy2_pos10);
            return thirdWave_2;
        case thirdWave_2:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos4);
            createEnemies(enemy1_pos10);
            createEnemies(enemy1_pos7);
            createEnemies(enemy1_pos5);
            createEnemies(enemy2_pos3);
            createEnemies(enemy2_pos2);
            return fourthWave_1;
        case fourthWave_1:
            createEnemies(enemy3_pos1);
            return fourthWave_2;
        case fourthWave_2:
            createEnemies(enemy1_pos1);
            createEnemies(enemy1_pos10);
            createEnemies(enemy3_pos4);
            return fifthWave_;
        case fifthWave_:
            createEnemies(enemy2_pos1);
            createEnemies(enemy2_pos5);
            createEnemies(enemy2_pos10);
            createEnemies(enemy3_pos4);
            createEnemies(enemy3_pos1);
            return 0;
    }
    return 0;
}

// bool asset::spawnWave(wave& deploy) {

    // static int enemies=0;
    // static int deployOrder=1;
    // static bool deployable=true;
    // if(enemies>=deploy.totalEnemies) {
    //     return true;
    // }
    // if(deployOrder==1 && deployable) {
    //     for(int j=0; j<deploy.deployWave_1.noEnemy1; j++) {
    //         createEnemies(enemy1_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_1.noEnemy2; j++) {
    //         createEnemies(enemy2_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_1.noEnemy3; j++) {
    //         createEnemies(enemy3_list[j]);
    //         enemies++;
    //     }
    //     deployable=false;
    // }
    // if(deployOrder==2 && deployable) {
    //     for(int j=0; j<deploy.deployWave_2.noEnemy1; j++) {
    //         createEnemies(enemy1_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_2.noEnemy2; j++) {
    //         createEnemies(enemy2_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_2.noEnemy3; j++) {
    //         createEnemies(enemy3_list[j]);
    //         enemies++;
    //     }
    //     deployable=false;
    // }
    // if(deployOrder==3 && deployable) {
    //     for(int j=0; j<deploy.deployWave_3.noEnemy1; j++) {
    //         createEnemies(enemy1_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_3.noEnemy2; j++) {
    //         createEnemies(enemy2_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_3.noEnemy3; j++) {
    //         createEnemies(enemy3_list[j]);
    //         enemies++;
    //     }
    //     deployable=false;
    // }
    // if(deployOrder==4 && deployable) {
    //     for(int j=0; j<deploy.deployWave_4.noEnemy1; j++) {
    //         createEnemies(enemy1_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_4.noEnemy2; j++) {
    //         createEnemies(enemy2_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_4.noEnemy3; j++) {
    //         createEnemies(enemy3_list[j]);
    //         enemies++;
    //     }
    //     deployable=false;
    // }
    // if(deployOrder==5 && deployable) {
    //     for(int j=0; j<deploy.deployWave_5.noEnemy1; j++) {
    //         createEnemies(enemy1_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_5.noEnemy2; j++) {
    //         createEnemies(enemy2_list[j]);
    //         enemies++;
    //     }
    //     for(int j=0; j<deploy.deployWave_5.noEnemy3; j++) {
    //         createEnemies(enemy3_list[j]);
    //         enemies++;
    //     }
    //     deployable=false;
    // }
    // if(m->getGroup(enemies).empty()) {deployOrder++; deployable=true;}
    // return false;
// }

// void asset::createHitfx(vector& position) {
//     auto p=new particleSystem(position.x, position.y);
//     std::unique_ptr<particleSystem> ptr{p};
//     game::particles.emplace_back(std::move(ptr));
// }