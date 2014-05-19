//
// Created by 杜一飞 on 14-5-11.
//

#include "BaseBiz.h"

PutShipViewer *BaseBiz::getPutShipViewer() {
    return PutShipViewer::getInstance();
}

GameStatus *BaseBiz::getGameStatus() {
    return GameStatus::getInstance();
}

BattleViewer *BaseBiz::getBattleViewer() {
    return BattleViewer::getInstance();
}

ForceType BaseBiz::getOtherForceType(ForceType forceType) {
    return forceType == Left ? Right : Left;
}
