#ifndef _COMPONENT_H
#define _COMPONENT_H

#include"entity.h"
#include"texture.h"
#include"collision.h"
#include"obj.h"
#include"fx.h"


class Texture;

class pos:public component{
    private:
        
    public:
        vector position;
        vector velocity;
        
        float offset_x;
        float offset_y;
        vector center;
        
        float acceleration;
        float speed=1;

        pos()=default;

        pos(const float& x_, const float& y_);

        pos(const float& x_, const float& y_, const float& offset_center_x, const float& offset_center_y);

        void setSpeed(float speed_);

        void stutter();
        
        ~pos() override;

        void init() override;
        void update() override;

};


class graphic:public component{
    private:
        pos* position;
        std::shared_ptr<Texture> texture;

        SDL_Rect src, dest;

        bool rotate;
        int frame=1;
        int speed=100;
        double angle;

        SDL_Point center;
    public:
        int w, h;
        bool animated;

        graphic()=default;

        graphic(const std::string& id, bool rotate_=false);
        graphic(const std::string& id, int frame_, int speed_, bool animated, bool rotate_=false);
        
        ~graphic() override {}

        void init() override;
        void update() override;
        void draw() override;
};

class keyboardHandler:public component{
    private:
        pos* position;
        
    public:
        static vector mousePos;

        void init() override;
        
        void update() override;
};


enum boundaryInteractions{
    ignore,
    destroy,
    condone
};

class collision:public component{
    private:    
        float r;
        
        std::shared_ptr<Texture> hitfx;
    public:
        int boundaryFlag;
        bool hit;
        int iframe=0;
        circle collider;
        SDL_Rect boundaryMark;
        pos* position;

        collision();
        collision(const float& r, const int& boundaryFlag=ignore);
        ~collision() override;

        void init() override;
        void update() override;
};

enum behaviorFlag{
    outside_the_stage,
    into_the_stage,
    random_movement,
    speedup_movement,
};

class behavior:public component{
    private:
        pos* position;
        vector target;
        int duration;
    public:
        int flag;
        vector dir;
        behavior(float x=0, float y=0);
        
        void init() override;
        void update() override;
        void draw() override;
};

enum muzzleConfigs {
    main_char_lv1, 
    main_char_lv2, 
    main_char_lv3,

    enemy_single_muzzle,
    enemy_2_muzzle_side_pods,
    enemy_2_muzzle_1_direction,
    enemy_4_muzzle_1_direction,
    enemy_4_muzzle_spread,
    enemy_4_muzzle_spread_spin
};

class muzzle:public component{
    private:
        pos* position;
        int numberOfMuzzles;
        

        unsigned int cooldown;
        unsigned int countCD;
        
        int deg;
    public:
        int flag;
        std::vector<vector> muzzlesDirection;
        static bool fire;
        bool shoot;
        static bool player_fire;
        
        muzzle(const int& flag_, const int& cooldown_);
        ~muzzle() override;

        vector direcion() const; 

        void init() override;
        void update() override;
        
};

class projectile:public component{
    private:
        float speed;
        vector direction;
        pos* position;
        collision* collider;
    public:
        projectile(const float& speed_, const vector& dir);
        ~projectile() override;

        void init() override;
        void update();
};

class state:public component{
    private:
        int tempHP;
    public:
        int hp;
        bool hp_down;

        state(const int& hp_);
        ~state() override;
        bool HPdown();
        void init() override;
        void update() override;
};



#endif
