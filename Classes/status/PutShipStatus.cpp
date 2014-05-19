//
// Created by 杜一飞 on 14-5-11.
//

#include "PutShipStatus.h"
#include "GameStatus.h"

void PutShipStatus::init() {
    currentForceType = Left;
}

Force *PutShipStatus::getCurrentForce() {
    Force *force = currentForceType == Left ?
                    GameStatus::getInstance()->leftForce :
                    GameStatus::getInstance()->rightForce;
    return force;
}

Ship *PutShipStatus::getCurrentShip() {
    Force *force = getCurrentForce();
    Ship *ship = force->getShipMap()[currentShipType];
    return ship;
}
