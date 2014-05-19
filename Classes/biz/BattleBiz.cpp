//
// Created by 杜一飞 on 14-5-17.
//

#include "BattleBiz.h"
#include "../config/ConfigManager.h"
#include "cocos2d.h"

USING_NS_CC;

BattleBiz *BattleBiz::INSTANCE = NULL;

void BattleBiz::init() {

}

void BattleBiz::enter() {
    getBattleStatus()->setForceType(Right); // 先打右边的
    getBattleStatus()->setRound(0);
    getBattleStatus()->setHitCountLeft(0);

    getBattleViewer()->enter();
    switchTurnTo(getBattleStatus()->getForceType(), false);
}


BattleStatus *BattleBiz::getBattleStatus() {
    return getGameStatus()->battleStatus;
}

void BattleBiz::hitMatrix(MatrixPos &pos) {
    int hitCountLeft = getGameStatus()->battleStatus->getHitCountLeft();

    if (hitCountLeft <= 0) {
        return;
    }

    hitCountLeft--;
    getBattleStatus()->setHitCountLeft(hitCountLeft);

    bool isHit = hitSea(pos);

    ForceType curForce = getBattleStatus()->getForceType();

    if (isHit) {
        getBattleViewer()->viewHit(pos, curForce);

        if (getCurrentForce()->isAllDestroyed()) {
            getBattleViewer()->showWinDialog(getOtherForceType(curForce));
        }
    } else {
        getBattleViewer()->viewMiss(pos, curForce);
    }

    getBattleViewer()->viewLastHitCount(hitCountLeft);

    if (hitCountLeft <= 0) {
        int round = getBattleStatus()->getRound();
        getBattleStatus()->setRound(++round);
        ForceType nextForce = getOtherForceType(curForce);
        switchTurnTo(nextForce);
    }
}


bool BattleBiz::hitSea(MatrixPos &pos) {

    Force *f = getCurrentForce();

    bool isHit = hitShip(f->getShipMap(), pos);

    SeaState state = isHit ? Hit : Miss;
    f->getSeaPad()->setState(pos.first, pos.second, state);

    return isHit;
}


Force *BattleBiz::getCurrentForce() {
    return getGameStatus()->battleStatus->getForceType() == Left ?
            getGameStatus()->leftForce : getGameStatus()->rightForce;
}

bool BattleBiz::hitShip(ShipMap &shipMap, MatrixPos &pos) {

    foreach(it, shipMap, ShipMap) {
        Ship *ship = (*it).second;

        if (ship->rotateType == Horizontal) {
            if (pos.second == ship->pos.second
                    && pos.first >= ship->pos.first
                    && pos.first < (ship->pos.first + ship->length)) {
                int shipPos = pos.first - ship->pos.first;
                ship->setHealth(shipPos, false);
                return true;
            }
        } else {
            if (pos.first == ship->pos.first
                    && pos.second <= ship->pos.second
                    && pos.second > (ship->pos.second - ship->length)) {
                int shipPos = ship->pos.second - pos.second;
                ship->setHealth(shipPos, false);
                return true;
            }
        }
    }

    return false;
}

void BattleBiz::switchTurnTo(ForceType forceType, bool showWait) {
    int round = getBattleStatus()->getRound();
    int hitCount = ConfigManager::getInstance()->getHitCountByRound(round);

    getBattleStatus()->setForceType(forceType);
    getBattleStatus()->setHitCountLeft(hitCount);

    ccSchedulerFunc cb = [this, forceType, hitCount, showWait](float d){
        this->getBattleViewer()->turnToForce(forceType);
        this->getBattleViewer()->viewLastHitCount(hitCount);
        if (showWait) {
            getBattleViewer()->stopWait();
        }
    };

    if (showWait) {
        getBattleViewer()->showWait();
        Director::getInstance()->getScheduler()->schedule(cb, this, 0, 0, 3, false, "turnNext");
    } else {
        cb(0);
    }


}
