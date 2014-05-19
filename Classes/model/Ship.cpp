//
// Created by 杜一飞 on 14-5-1.
//

#include "Ship.h"

#include "../util/CommonUtils.h"

Ship::Ship(int id, const std::string &type, int length):id(id), type(type), length(length), rotateType(Vertical) {
    health = new bool[length];
    memset(health, true, length);
}

Ship::~Ship() {
    delete [] health;
}


void Ship::setHealth(int pos, bool isHealth) {
    *(this->health + pos) = isHealth;
}

bool Ship::isDestroy() {
    fori(i, 0, this->length) {
        if (*(health + i)) {
            return false;
        }
    }
    return true;
}
