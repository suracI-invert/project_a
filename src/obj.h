#ifndef _OBJ_H
#define _OBJ_H

#include"texture.h"
#include<vector>


class object{
    private:
        double x_, y_;
        Texture* texture;
        
    public:
        object(double x, double y, const std::string path, SDL_Renderer* render);
        
        double x() const;
        double y() const;

        void graphic_out(SDL_Renderer* render, SDL_Rect* sprites=nullptr);
        


};



#endif