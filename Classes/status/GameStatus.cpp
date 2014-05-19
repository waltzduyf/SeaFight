//
// Created by 杜一飞 on 14-5-11.
//

#include "GameStatus.h"

GameStatus *GameStatus::INSTANCE = NULL;

void GameStatus::init() {
    gameState = Menu;
    leftForce = NULL;
    rightForce = NULL;

    initStatus();
}

GameStatus::~GameStatus() {
    delete putShipStatus;
    delete battleStatus;
}

void GameStatus::initStatus() {
    if (leftForce != NULL) {
        delete leftForce;
    }
    if (rightForce != NULL) {
        delete rightForce;
    }

    leftForce = new Force;
    leftForce->setType(Left);
    leftForce->setSeaPad(new SeaPad(SEA_PAD_PICE_ROW, SEA_PAD_PICE_ROW));
    rightForce = new Force;
    rightForce->setType(Right);
    rightForce->setSeaPad(new SeaPad(SEA_PAD_PICE_ROW, SEA_PAD_PICE_ROW));

    this->putShipStatus = new PutShipStatus;
    this->putShipStatus->init();

    this->battleStatus = new BattleStatus;
    this->battleStatus->init();
}
