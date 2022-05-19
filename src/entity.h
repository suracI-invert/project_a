#ifndef _ENTITY_H
#define _ENTITY_H

#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<bitset>
#include<array>

#include"texture.h"

class manager;
class entity;
class component;

using ID=std::size_t;
using group=std::size_t;

inline ID getTypeID() {
    static ID lastID=0u;
    return ++lastID;
}

template<typename T> inline ID getTypeID() {
    static ID typeID=getTypeID();
    return typeID;
}

constexpr std::size_t maxComponents=32;
constexpr std::size_t maxGroups=32;

using componentStates=std::bitset<maxComponents>;
using componentList=std::array<component*, maxComponents>;

using groupStates=std::bitset<maxGroups>;


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
        manager& manager_;
        
        std::vector<std::unique_ptr<component>> components;
        componentStates c_states;
        componentList c_list;

        groupStates g_states;
    public:
        bool active=true;

        entity(manager& m):manager_(m) {}

        ~entity() {std::cout<<"entity destroyed! \n";}
        
        void update() {
            for(auto& c:components) c->update();
        }
        void draw() {
            for(auto& c:components) c->draw();
        }
        
        void destroy() {active=false;}

        template<typename T> bool hasComponent() const {return c_states[getTypeID<T>()];}

        template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->entity=this;
            std::unique_ptr<component> ptr{c};
            if(!ptr) throw std::runtime_error{"can't add components!"};
            components.emplace_back(std::move(ptr));
            c_list[getTypeID<T>()]=c;
            c_states[getTypeID<T>()]=true;

            c->init();
            return *c;
        }

        template<typename T> T& getComponent() const {
            auto ptr(c_list[getTypeID<T>()]);
            return *static_cast<T*> (ptr);
        }

        bool hasGroup(group group_) {return g_states[group_];}

        void addGroup(group group_);

        void delGroup(group group_) {g_states[group_]=false;}
};

class manager{
    private:
        std::vector<std::unique_ptr<entity>> e_list;
        std::array<std::vector<entity*>, maxGroups> e_group;

    public:
        ~manager() {std::cout<<"manager destroyed! \n";}

        void update() {
            for(auto& e:e_list) e->update();
        }

        void draw() {
            for(auto& e:e_list) e->draw();
        }

        void reset() {
            for(auto i=0; i<maxGroups; i++) {
                auto& v=e_group[i];
                v.erase(std::remove_if(v.begin(), v.end(), [i](entity* e ){return !e->active || !e->hasGroup(i);}), v.end());
            }
            e_list.erase(std::remove_if(e_list.begin(), e_list.end(),[](std::unique_ptr<entity>& e)->bool{return !e->active;}), e_list.end());
        }

        void addToGroup(entity* e, group g) {
             e_group[g].emplace_back(e);
        }

        std::vector<entity*>& getGroup(group g) {
            return e_group[g];
        }

        entity& addEntity() {
            entity* e=new entity(*this);
            std::unique_ptr<entity> ptr{e};
            e_list.emplace_back(std::move(ptr));
            return *e;
        }
};

#endif