#ifndef _GAME_STATE_H
#define _GAME_STATE_H



class gameState{
    private:

    public: 
        virtual ~gameState() {}
        virtual void spawn() {}
        virtual void update() {}
};

#endif
