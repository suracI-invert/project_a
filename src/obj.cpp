#include"obj.h"


//object
object::object(double x, double y, const std::string path, SDL_Renderer* render) {
    x_=x; 
    y_=y;
    texture=new Texture{path, render};
    
}

double object::x() const {return x_;}
double object::y() const {return y_;}

//merge all assest of one object into one png file and do sprites
void object::graphic_out(SDL_Renderer* render, SDL_Rect* sprites=nullptr) {
    texture->renderOut(render, x_, y_, sprites);
}
