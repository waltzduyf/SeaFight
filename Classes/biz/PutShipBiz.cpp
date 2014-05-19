//
// Created by 杜一飞 on 14-5-11.
//

#include "PutShipBiz.h"
#include "../view/ViewConsts.h"
#include "../config/ConfigManager.h"
#include "BattleBiz.h"
#include "Surrounder.h"

#include "../util/CommonUtils.h"

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

static const string PUT_ORDER[] = { SHIP_TYPE_CARRIER, SHIP_TYPE_CRUISER, SHIP_TYPE_DESTROYER, SHIP_TYPE_SUBMARINE, SHIP_TYPE_FRIGATE };
static const int SHIP_TYPE_COUNT = sizeof(PUT_ORDER) / sizeof(string);

PutShipBiz *PutShipBiz::INSTANCE = NULL;

static string getNextShip(string type) {
    if (type.size() == 0) {
        return PUT_ORDER[0];
    }

    fori(i, 0, SHIP_TYPE_COUNT) {
        if (type == PUT_ORDER[i] && i != SHIP_TYPE_COUNT - 1) {
            return PUT_ORDER[++i];
        }
    }
    return "";
}

PutShipStatus *PutShipBiz::getPutShipStatus() {
    return getGameStatus()->putShipStatus;
}

void PutShipBiz::init() {
}

void PutShipBiz::enter() {
    getPutShipStatus()->currentForceType = Left;
    getPutShipStatus()->currentShipType = "";

    getGameStatus()->initStatus();

    getPutShipViewer()->intoScene();
    getPutShipViewer()->initSea();
    getPutShipViewer()->showForceType(getPutShipStatus()->currentForceType);
    putInNextShip();
}


Ship* PutShipBiz::putInNextShip() {
    Ship *next = createNextShip();
    if (next == NULL) {
        return NULL;
    }

    Force *force = getGameStatus()->putShipStatus->getCurrentForce();
    force->addShip(next);

    // 如果重叠，则向右一格，如果一行满了，则从下一行开始再算
    MatrixPos pos = next->pos;
    while (isOverlapping(next, next->rotateType, pos)) {
        if (pos.first < SEA_PAD_PICE_ROW - 1) {
            pos = MatrixPos(pos.first + 1, pos.second);
        } else {
            pos = MatrixPos(0, pos.second - 1);
        }
    }
    next->pos = pos;

    getPutShipViewer()->putInShip(next);
    getPutShipStatus()->currentShipType = next->type;
    return next;
}

Ship *PutShipBiz::createNextShip() {

    string nextType = getNextShip(getPutShipStatus()->currentShipType);
    if (nextType.size() == 0) {
        return NULL;
    }

    Ship *next = createFromPrototype(nextType);
    next->pos.first = 0;
    next->pos.second = 9;
    return next;
}

Ship *PutShipBiz::createFromPrototype(std::string type) {
    Ship *prototype = ConfigManager::getInstance()->getShipModels()[type];

    Ship *newInstance = new Ship(generateShipId(), type, prototype->length);

    return newInstance;
}

int PutShipBiz::generateShipId() {

    static int wholeId = 0;

    return wholeId++;
}


void PutShipBiz::switchRotation() {
    Ship *ship = getPutShipStatus()->getCurrentShip();
    RotateType r = ship->rotateType == Vertical ? Horizontal : Vertical;

    if (isOut(ship, r, ship->pos)) {
        return;
    }

    // 如果重叠了，就不动了
    if (isOverlapping(ship, r, ship->pos)) {
        return;
    }

    ship->rotateType = r;
    getPutShipViewer()->rotateTo(ship, r);
}

void PutShipBiz::moveCurrentShipTo(const MatrixPos &pos) {
    Ship *ship = getPutShipStatus()->getCurrentShip();

    MatrixPos tryPos = pos;
    // 判断是否超出范围
    if (isOut(ship, ship->rotateType, pos)) {
        if (ship->rotateType == Horizontal) {
            tryPos = MatrixPos(SEA_PAD_PICE_ROW - ship->length, pos.second);
        } else {
            tryPos = MatrixPos(pos.first, ship->length - 1);
        }
    }

    // 判断是否与其他船重叠
    Surrounder s;
    while (isOverlapping(ship, ship->rotateType, tryPos)
            || isOut(ship, ship->rotateType, tryPos)) {
        MatrixPos nextOffset = s.nextPos();
        tryPos = MatrixPos(tryPos.first + nextOffset.first, tryPos.second + nextOffset.second);
    }

    ship->pos = tryPos;
    getPutShipViewer()->moveShip(ship);
}

void PutShipBiz::settleAndPutNext() {
    Ship *ship = getPutShipStatus()->getCurrentShip();
    getPutShipViewer()->settleShip(ship);

    Ship *next = putInNextShip();
    if (next == NULL) {
        switchToNextForce();
    }
}


void PutShipBiz::switchToNextForce() {
    if (getPutShipStatus()->currentForceType == Right) {
        BattleBiz::getInstance()->enter();
        return;
    }

    getPutShipStatus()->currentForceType = Right;
    getPutShipStatus()->currentShipType = "";

    getPutShipViewer()->initSea();
    getPutShipViewer()->showForceType(getPutShipStatus()->currentForceType);
    putInNextShip();
}


Force *PutShipBiz::getCurrentForce() {
    return getPutShipStatus()->currentForceType == Left ? getGameStatus()->leftForce : getGameStatus()->rightForce;
}

static Rect getShipRect(Ship *ship, RotateType rotateType, const MatrixPos &pos) {
    if (rotateType == Horizontal) {
        float width = ship->length - 0.5;
        float height = 0.5;

        return Rect(pos.first, pos.second - 1, width, height);
    } else {
        float width = 0.5;
        float height = ship->length - 0.5;

        return Rect(pos.first, pos.second - ship->length, width, height);
    }
}

bool PutShipBiz::isOut(Ship *curShip, RotateType rotateType, const MatrixPos &pos) {
    int x, y, width, height;
    if (rotateType == Horizontal) {
        x = 0;
        y = 0;
        width = SEA_PAD_PICE_ROW - curShip->length;
        height = SEA_PAD_PICE_ROW - 1;
    } else {
        x = 0;
        y = curShip->length - 1;
        width = SEA_PAD_PICE_ROW - 1;
        height = SEA_PAD_PICE_ROW - 1;
    }

    return pos.first < x || pos.first > width || pos.second < y || pos.second > height;
}

bool PutShipBiz::isOverlapping(Ship *curShip, RotateType rotateType, const MatrixPos &pos) {
    Force *f = getCurrentForce();
    Rect curRect = getShipRect(curShip, rotateType, pos);
    foreach(it, f->getShipMap(), ShipMap) {
        Ship *temp = (*it).second;
        if (temp == curShip) {
            continue;
        }

        Rect tempRect = getShipRect(temp, temp->rotateType, temp->pos);

        if (tempRect.intersectsRect(curRect)) {
            return true;
        }
    }

    return false;
}
