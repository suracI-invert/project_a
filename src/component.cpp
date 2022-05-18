#include"component.h"

pos::pos(float x_, float y_) {
    position.x=x_;
    position.y=y_;
}

void pos::setSpeed(float speed_) {speed=speed_;}

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

graphic::graphic(const char* path, SDL_Point center_) {
    texture=std::unique_ptr<Texture> {new Texture{path}};

    src.w=texture->getWidth();
    src.h=texture->getHeight();

    dest.w=texture->getWidth();
    dest.h=texture->getHeight();

    rotate=true;
    center=center_;
}

void graphic::init() {
    position=&entity->getComponent<pos>();

    src.x=src.y=0;

    w=texture->getWidth();
    h=texture->getHeight();

    angle=90;
}

void graphic::update() {
    dest.x=(float)position->position.x;
    dest.y=(float)position->position.y;

    vector centerPos{};
    centerPos.x=position->position.x+center.x;
    centerPos.y=position->position.y+center.y;

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
}


collision::collision() {
    this->offset_x=0;
    this->offset_y=0;
    this->r=0;
}

collision::collision(float offset_x, float offset_y, float r, bool hostile, int boundaryFlag) {
    this->offset_x=offset_x;
    this->offset_y=offset_y;
    this->r=r;
    this->boundaryFlag=boundaryFlag;
    this->hostile=hostile;
}

void collision::init() {
    position=&entity->getComponent<pos>();
    collider.r=r;
    boundaryMark.w=(int)entity->getComponent<graphic>().w;
    boundaryMark.w=(int)entity->getComponent<graphic>().h;

    if(hostile) game::threatColliders.push_back(&collider);
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

behavior::behavior(float x, float y) {
    this->dir.x=x;
    this->dir.y=y;
}

void behavior::init() {
    position=&entity->getComponent<pos>();
    target={0, 0};
}

void behavior::update() {
    dir=position->position.direction(*game::playerPos);
    
    entity->getComponent<pos>().velocity=dir;
}

void behavior::draw() {
    std::cout<<"enemy: \n"<<"x: "<<position->position.x<<" y: "<<position->position.y<<std::endl
             <<"velocity-> x: "<<position->velocity.x<<" y: "<<position->velocity.y<<std::endl
             <<"direction->x: "<<dir.x<<" y: "<<dir.y<<std::endl
             <<"target->x: "<<target.x<<" y: "<<target.y<<std::endl;
}
