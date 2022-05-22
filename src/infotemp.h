#ifndef _INFOTEMP_H
#define _INFOTEMP_H

#include<iostream>



struct object{
    struct posComponent{
        float x, y, offset_center_x, offset_center_y, speed;
    } position;

    struct graphicComponent{
        std::string id;
        bool rotate;
    } graphic;

    struct collisionComponent{
        float radius;
        int boundaryFlag;
    } collision;

    struct behaviorComponent{
        float x, y;
    } behavior;

    struct muzzleComponent{
        int flag, cooldown;
    } muzzle;

    struct stateComponent{
        int hp;
    } state;
}extern enemy1_pos1, enemy1_pos2, enemy1_pos3, enemy1_pos4, enemy1_pos5, enemy1_pos6, enemy1_pos7, enemy1_pos8, enemy1_pos9, enemy1_pos10,
        enemy2_pos1, enemy2_pos2, enemy2_pos3, enemy2_pos4, enemy2_pos5, enemy2_pos6, enemy2_pos7, enemy2_pos8, enemy2_pos9, enemy2_pos10,
        enemy3_pos1, enemy3_pos2, enemy3_pos3, enemy3_pos4; 

// extern object enemy1_list[10];
// extern object enemy2_list[10];
// extern object enemy3_list[4];



// struct wave{
//     int totalEnemies;
//     struct deployment{
//         int noEnemy1, noEnemy2, noEnemy3;
//     }deployWave_1, deployWave_2, deployWave_3, deployWave_4, deployWave_5;
// }extern first, second, third, fourth, fifth;

#endif