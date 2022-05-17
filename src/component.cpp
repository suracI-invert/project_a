#include"component.h"

pos::pos(float x_, float y_) {
    position.x=x_;
    position.y=y_;
}

void pos::init() {
    velocity.x=0;
    velocity.y=0;
}

void pos::update() {
    position=position+velocity.normalize()*speed;
}

pos::~pos() {}

graphic::graphic(const char* path) {
    texture=std::unique_ptr<Texture> {new Texture{path}};

    src.w=texture->getWidth();
    src.h=texture->getHeight();

    dest.w=texture->getWidth();
    dest.h=texture->getHeight();
}

void graphic::init() {
    position=&entity->getComponent<pos>();

    src.x=src.y=0;

    w=texture->getWidth();
    h=texture->getHeight();
}

void graphic::update() {
    dest.x=(float)position->position.x;
    dest.y=(float)position->position.y;
}

void graphic::draw() {
    texture->renderOut(&src, &dest);
}


void keyboardHandler::init() {
    position=&entity->getComponent<pos>();
}

void keyboardHandler::update() {
    if(game::e.type==SDL_KEYDOWN&&game::e.key.repeat==0) {
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

    if(game::e.type==SDL_KEYUP&&game::e.key.repeat==0) {
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
    }
}


collision::collision() {
    this->offset_x=0;
    this->offset_y=0;
    this->r=0;
}

collision::collision(float offset_x, float offset_y, float r, int boundaryFlag) {
    this->offset_x=offset_x;
    this->offset_y=offset_y;
    this->r=r;
    this->boundaryFlag=boundaryFlag;
}

void collision::init() {
    position=&entity->getComponent<pos>();
    collider.r=r;
    boundaryMark.w=(int)entity->getComponent<graphic>().w;
    boundaryMark.w=(int)entity->getComponent<graphic>().h;
}

void collision::update() {
    boundaryMark.x=position->position.x;
    boundaryMark.y=position->position.y;

    collider.x=position->position.x+offset_x;
    collider.y=position->position.y+offset_y;

    if(boundaryFlag==condone) {
        switch(withinBoundary(boundaryMark)) {
            case top:
                entity->getComponent<pos>().position.y=0;
                break;
            case down:
                entity->getComponent<pos>().position.y=game::h;
                break;
            case left:
                entity->getComponent<pos>().position.x=0;
                break;
            case right:
                entity->getComponent<pos>().position.x=game::w;
                break;
            case inside:
                break;
        }
    }
}
