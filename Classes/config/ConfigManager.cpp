//
// Created by 杜一飞 on 14-5-11.
//

#include "ConfigManager.h"
#include "../model/Ship.h"

ConfigManager *ConfigManager::INSTANCE = NULL;

void ConfigManager::init() {
    //初始化舰船的配置
    initShip();
    initHitCount();
}

ShipMap &ConfigManager::getShipModels() {
    return shipMap;
}

void ConfigManager::initShip() {
    Ship *frigate = new Ship(0, SHIP_TYPE_FRIGATE, 2);
    addShipPrototype(frigate);
    Ship *submarine = new Ship(0, SHIP_TYPE_SUBMARINE, 3);
    addShipPrototype(submarine);
    Ship *destroyer = new Ship(0, SHIP_TYPE_DESTROYER, 3);
    addShipPrototype(destroyer);
    Ship *cruiser = new Ship(0, SHIP_TYPE_CRUISER, 4);
    addShipPrototype(cruiser);
    Ship *carrier = new Ship(0, SHIP_TYPE_CARRIER, 5);
    addShipPrototype(carrier);
}

void ConfigManager::addShipPrototype(Ship *ship) {
    shipMap[ship->type] = ship;
}

int ConfigManager::getHitCountByRound(int round) {
    int roundStep = -1;
    foreach(it, roundArray, RoundArray) {
        roundStep = *it;
        if (round >= roundStep) {
            break;
        }
    }

    if (roundStep == -1) {
        LOG("round step is not find, this round %d", round);
    }

    int hitCount = hitCountMap[roundStep];

    return hitCount;
}


void ConfigManager::initHitCount() {
    addHitCountConfig(0, 5);
    addHitCountConfig(6, 4);
    addHitCountConfig(12, 3);
    addHitCountConfig(18, 2);
    addHitCountConfig(24, 1);
}


void ConfigManager::addHitCountConfig(int round, int hitCount) {
    roundArray.push_back(round);
    hitCountMap[round] = hitCount;
}
