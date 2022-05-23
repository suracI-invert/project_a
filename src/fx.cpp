#include"fx.h"
#include"texture.h"

UI::UI(int frame_, const char* path) {
   frame=frame_;
   texture=new Texture{path};
   dest={0, 0, texture->getWidth()/frame, texture->getHeight()};
   src={};
}
UI::~UI() {
   texture->~Texture();
};

void UI::update(int current) {
   src={(texture->getWidth()/frame)*(current-1), 0, texture->getWidth()/frame, texture->getHeight()};
}
void UI::draw() {
   texture->renderOut(&src, &dest);
}


// particle::particle(float x_, float y_) {
//     x=x_;
//     y=y_;
//     texture=game::assetManager->GetTexture("particle");
    
//     // frame=;
//     // float vx=1*cosf;
//     // float vy=1*sinf;
//     // velo={vx*frame, vy*frame};
// }

// particle::~particle() {}

// void particle::update() {
//     x+=velo.x;
//     y+=velo.y;
//     frame++;
// }

// void particle::draw() {
//     dest={(int)x, (int)y, texture->getWidth(), texture->getHeight()};
//     texture->renderOut(nullptr, &dest);
// }

// bool particle::dead() {return frame>10;}

// particleSystem::particleSystem(float x, float y) {
//     for(int i=0; i<TOTAL_PARTICLES; i++) {
//         particles.push_back(new particle{x, y});
//     }
// }

// particleSystem::~particleSystem() {
//     for(auto p:particles) delete p;
// }

// bool particleSystem::empty() {return particles.empty(); std::cout<<"particle system delete\n";}

// void particleSystem::draw() {
//     for(auto p:particles) p->draw();
//     for(auto p:particles) {
//         if(p->dead()) {delete p;}
//     }
// }

// hitfx::hitfx(float x_, float y_) {
//     int x=(int)x_;
//     int y=(int)y_;
//     texture=game::assetManager->GetTexture("hitfx");
//     frame=0;
// }

// bool hitfx::end() {return frame==5;}

// void hitfx::draw() {
//     dest={x, y, texture->getWidth(), texture->getHeight()};
//     texture->renderOut(nullptr, &dest);
//     std::cout<<frame<<std::endl;
//     frame++;
// }

// deadfx::deadfx(float x_, float y_) {
//     int x=(int)x_;
//     int y=(int)y_;
//     texture=game::assetManager->GetTexture("hitfx");
//     frame=1;
// }

// bool deadfx::end() {return frame==6;} 

// void deadfx::draw() {
//     dest={x, y, texture->getWidth()*frame, texture->getHeight()*frame};
//     texture->renderOut(nullptr, &dest);
//     frame++;
// }

void DrawCircle( int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);
   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(game::renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(game::renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(game::renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(game::renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(game::renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(game::renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(game::renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(game::renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}