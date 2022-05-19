#include"entity.h"

void entity::addGroup(group group_) {
    g_states[group_]=true;
    manager_.addToGroup(this, group_);
}