#include"component.h"

pos::pos(double x_, double y_) {
    x=x_;
    y=y_;
}

pos::~pos() {}

void pos::init() {
    x=0;
    y=0;
}

void pos::setPos(double x_, double y_) {
    x=x_;
    y=y_;
}

void pos::update(){
    x++;
    y++;
}

sprite::sprite(const char* path){
    
    texture=std::unique_ptr<Texture> {new Texture{path}};
            

            
    
    src.w=texture->getWidth();
    src.h=texture->getHeight();
    

    dest.w=texture->getWidth();
    dest.h=texture->getHeight();
            
            
}

void sprite::init() {
    position=&entity->getComponent<pos>();

    src.x=src.y=0;
}

void sprite::update(){
    dest.x=position->x;
    dest.y=position->y;
}

void sprite::draw(){
    texture->renderOut(&src, &dest);
    std::cout<<"render image \n";
}

sprite::~sprite() {}