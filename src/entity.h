#ifndef _ENTITY_H
#define _ENTITY_H

#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<bitset>
#include<array>

#include"texture.h"

class component;
class entity;

using ID=std::size_t;

inline ID getTypeID() {
    static ID lastID=0;
    return ++lastID;
}

template<typename T> inline ID getTypeID() {
    static ID typeID=getTypeID();
    return typeID;
}

constexpr std::size_t maxComponents=32;

using componentStates=std::bitset<maxComponents>;
using componentList=std::array<component*, maxComponents>;

class component{
    public:
        entity* entity;
        
        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}

        virtual ~component() {}
};

class entity{
    private:
        std::vector<std::unique_ptr<component>> components;
        componentStates states;
        componentList list;
    public:
        bool active=true;

        ~entity() {std::cout<<"entity destroyed! \n";}
        
        void update() {
            for(auto& c:components) c->update();
        }
        void draw() {
            for(auto& c:components) c->draw();
        }
        
        void destroy() {active=false;}

        template<typename T> bool hasComponent() const {return states[getTypeID<T>()];}

        template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->entity=this;
            std::unique_ptr<component> ptr{c};
            if(!ptr) throw std::runtime_error{"can't add components!"};
            components.emplace_back(std::move(ptr));
            list[getTypeID<T>()]=c;
            states[getTypeID<T>()]=true;

            c->init();
            return *c;
        }

        template<typename T> T& getComponent() const {
            auto ptr(list[getTypeID<T>()]);
            return *static_cast<T*> (ptr);
        }
};

class manager{
    private:
        std::vector<std::unique_ptr<entity>> list;

    public:
        ~manager() {std::cout<<"manager destroyed! \n";}

        void update() {
            for(auto& e:list) e->update();
        }

        void draw() {
            for(auto& e:list) e->draw();
        }

        void reset() {
            list.erase(std::remove_if(list.begin(), list.end(),[](std::unique_ptr<entity>& e)->bool{return !e->active;}), list.end());
        }

        entity& addEntity() {
            entity* e=new entity();
            std::unique_ptr<entity> ptr{e};
            list.emplace_back(std::move(ptr));
            return *e;
        }
};

#endif