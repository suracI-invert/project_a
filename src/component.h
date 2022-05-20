#ifndef _COMPONENT_H
#define _COMPONENT_H

#include"entity.h"
#include"texture.h"
#include"collision.h"
#include"obj.h"


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
        double angle;

        SDL_Point center;
    public:
        int w, h;

        graphic()=default;

        graphic(const std::string& id, bool rotate_=false);
        
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
        int boundaryFlag;
    public:
        circle collider;
        SDL_Rect boundaryMark;
        pos* position;

        collision();
        collision(const float& r, const int& boundaryFlag=ignore);
        ~collision() override;

        void init() override;
        void update() override;
};

class behavior:public component{
    private:
        pos* position;
        vector dir;
        vector target;
    public:
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
        std::vector<vector> muzzlesDirection;

        int flag;
        unsigned int cooldown;
        unsigned int countCD;
        
        
    public:
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


#endif
