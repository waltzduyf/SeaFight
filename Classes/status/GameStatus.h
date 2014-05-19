//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __SeaStatus_H_
#define __SeaStatus_H_

#include "../util/CommonUtils.h"
#include "PutShipStatus.h"
#include "BattleStatus.h"
#include "../model/Force.h"

enum GameState {
    Menu = 0,
    PutShip,
    Fight,
    Victory
};

class GameStatus {
    SINGLETON_FUNC(GameStatus)
public:
    GameState gameState;
    PutShipStatus *putShipStatus;
    BattleStatus *battleStatus;
    Force *leftForce;
    Force *rightForce;

    void initStatus();

    ~GameStatus();
};


#endif //__SeaStatus_H_
