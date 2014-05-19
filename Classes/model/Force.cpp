//
// Created by 杜一飞 on 14-5-11.
//

#include "Force.h"

#include "../util/CommonUtils.h"


void Force::addShip(Ship *ship) {
    shipMap[ship->type] = ship;
}


Ship *Force::getShipById(int id) {
    foreach(it, shipMap, ShipMap) {
        auto ship = (*it).second;
        if (ship->id == id) {
            return ship;
        }
    }
    return nullptr;
}

bool Force::isAllDestroyed() {
    foreach (it, shipMap, ShipMap) {
        if (! (*it).second->isDestroy()) {
            return false;
        }
    }
    return true;
}