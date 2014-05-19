//
// Created by 杜一飞 on 14-5-17.
//


#ifndef __BattleBiz_H_
#define __BattleBiz_H_

#include "BaseBiz.h"
#include "../model/ModelCommon.h"
#include "../status/BattleStatus.h"

class BattleBiz : public BaseBiz {
    SINGLETON_FUNC(BattleBiz);
public:
    void enter();
    void hitMatrix(MatrixPos &pos);

private:
    BattleStatus* getBattleStatus();

    bool hitSea(MatrixPos &pos);
    Force* getCurrentForce();
    bool hitShip(ShipMap &ship, MatrixPos &pos);

    void switchTurnTo(ForceType forceType, bool showWait = true);
};


#endif //__BattleBiz_H_
