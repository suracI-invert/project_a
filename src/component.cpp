#include"component.h"
#include"game.h"

pos::pos(const float& x_, const float& y_) {
    position.x=x_;
    position.y=y_;
}

pos::pos(const float& x_, const float& y_, const float& offset_center_x, const float& offset_center_y) {
    position.x=x_;
    position.y=y_;

    offset_x=offset_center_x;
    offset_y=offset_center_y;
}

void pos::setSpeed(float speed_) {speed=speed_;}

void pos::init() {
    velocity.x=0;
    velocity.y=0;
    
}

void pos::update() {
    
    position=position+velocity.normalize()*speed;
    center.x=position.x+offset_x;
    center.y=position.y+offset_y;
}

pos::~pos() {}

graphic::graphic(const std::string& id, bool rotate_) {
    texture=game::assetManager->GetTexture(id);

    src.w=texture->getWidth();
    src.h=texture->getHeight();

    dest.w=texture->getWidth();
    dest.h=texture->getHeight();

    rotate=rotate_;
}

void graphic::init() {
    position=&entity->getComponent<pos>();

    src.x=src.y=0;

    w=texture->getWidth();
    h=texture->getHeight();

    angle=90;
    center.x=position->offset_x;
    center.y=position->offset_y;
}

void graphic::update() {
    dest.x=(int)position->position.x;
    dest.y=(int)position->position.y;

    vector centerPos=position->center;

    if(centerPos!=keyboardHandler::mousePos) {
        vector directionToMouse=centerPos.direction(keyboardHandler::mousePos);
        angle=radToDeg(directionToMouse.rad())+90;
    }
}

void graphic::draw() {
    if(!rotate) texture->renderOut(&src, &dest);
    else texture->renderOut(&src, &dest, angle, &center);
}


vector keyboardHandler::mousePos;

void keyboardHandler::init() {
    position=&entity->getComponent<pos>();
    mousePos={0, 0};
}

void keyboardHandler::update() {
    if(game::e.type==SDL_KEYDOWN) {
        switch(game::e.key.keysym.sym) {
            case SDLK_w:
                position->velocity.y=-1;
                break;

            case SDLK_s:
                position->velocity.y=1;
                break;

            case SDLK_a:
                position->velocity.x=-1;
                break;

            case SDLK_d:
                position->velocity.x=1;
                break;

            default:
                break;
        }
    }

    if(game::e.type==SDL_KEYUP) {
        switch(game::e.key.keysym.sym) {
            case SDLK_w:
                position->velocity.y=0;
                break;

            case SDLK_s:
                position->velocity.y=0;
                break;

            case SDLK_a:
                position->velocity.x=0;
                break;

            case SDLK_d:
                position->velocity.x=0;
                break;

            default: 
                break;
        }
    }    
    
    if(game::e.type==SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        mousePos.x=x;
        mousePos.y=y;
    }

    if(game::e.type==SDL_MOUSEBUTTONDOWN&&game::e.button.button==SDL_BUTTON_LEFT) {muzzle::fire=true; std::cout<<"shoot! \n";}
    if(game::e.type==SDL_MOUSEBUTTONUP&&game::e.button.button==SDL_BUTTON_LEFT) muzzle::fire=false;
}


collision::collision() {
    this->r=0;
}

collision::collision(const float& r, const int& boundaryFlag) {
    this->r=r;
    this->boundaryFlag=boundaryFlag;
}

collision::~collision() {}

void collision::init() {
    position=&entity->getComponent<pos>();
    collider.r=r;
    boundaryMark.w=entity->getComponent<graphic>().w;
    boundaryMark.h=entity->getComponent<graphic>().h;
}

void collision::update() {
    boundaryMark.x=position->position.x;
    boundaryMark.y=position->position.y;

    collider.x=position->center.x;
    collider.y=position->center.y;

    

    if(boundaryFlag==condone) {
        switch(withinBoundary(boundaryMark)) {
            case top:
                entity->getComponent<pos>().position.y=0;
                break;
            case down:
                entity->getComponent<pos>().position.y=game::h-boundaryMark.h;
                break;
            case left:
                entity->getComponent<pos>().position.x=0;
                break;
            case right:
                entity->getComponent<pos>().position.x=game::w-boundaryMark.w;
                break;
            case inside:
                break;
        }
    }

    if(boundaryFlag==destroy) {
        if(withinBoundary(boundaryMark)!=inside) entity->destroy();
    }

}

behavior::behavior(float x, float y) {
    this->dir.x=x;
    this->dir.y=y;
}

void behavior::init() {
    position=&entity->getComponent<pos>();
    target={0, 0};
}

void behavior::update() {
    dir=position->center.direction(*game::playerPos);
    
    entity->getComponent<pos>().velocity=dir;
}

void behavior::draw() {}

bool muzzle::fire;

muzzle::muzzle(const int& flag_, const int& cooldown_) {
    cooldown=cooldown_;
    
    flag=flag_;
    switch(flag) {
        case main_char_lv1:
            numberOfMuzzles=1;
            for(int i=0;i<numberOfMuzzles;i++) {
                muzzlesDirection.push_back(vector{0, 0});
            }
            break;
        case main_char_lv2:
            break;
        case main_char_lv3:
            break;
        case enemy_single_muzzle:
            numberOfMuzzles=1;
            for(int i=0;i<numberOfMuzzles;i++) {
                muzzlesDirection.push_back(vector{0, 0});
            }
            break;
        case enemy_2_muzzle_1_direction:
            break;
        case enemy_2_muzzle_side_pods:
            break;
        case enemy_4_muzzle_1_direction:
            break;
        case enemy_4_muzzle_spread:
            break;
        case enemy_4_muzzle_spread_spin:
            break;
    }
}

muzzle::~muzzle() {}

vector muzzle::direcion() const {return muzzlesDirection[0];}

void muzzle::init() {
    position=&entity->getComponent<pos>();
    numberOfMuzzles=0;
    countCD=0;
    shoot=false;
}

void muzzle::update() {
    switch(flag) {
        case main_char_lv1:
            muzzlesDirection[0]=position->center.direction(keyboardHandler::mousePos);
            if(countCD==0&&fire) {
                countCD=cooldown;
                shoot=true;
            }
            else if(countCD!=0) {
                countCD--;
                
                shoot=false;
            }
            else shoot=false;

            break;
        case main_char_lv2:
            break;
        case main_char_lv3:
            break;
        case enemy_single_muzzle:
            muzzlesDirection[0]=position->center.direction(*game::playerPos);

            if(countCD==0) {
                countCD=cooldown; 
                shoot=true;
            }
            else {
                countCD--;
                shoot=false;
            }

            break;
        case enemy_2_muzzle_1_direction:
            break;
        case enemy_2_muzzle_side_pods:
            break;
        case enemy_4_muzzle_1_direction:
            break;
        case enemy_4_muzzle_spread:
            break;
        case enemy_4_muzzle_spread_spin:
            break;
    }

}

projectile::projectile(const float& speed_, const vector& dir) {speed=speed_; direction=dir;}

projectile::~projectile() {}

void projectile::init() {
    position=&entity->getComponent<pos>();
    position->velocity=direction;
    collider=&entity->getComponent<collision>();
    position->setSpeed(speed);
}

void projectile::update() {}
    