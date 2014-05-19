//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __BaseBiz_H_
#define __BaseBiz_H_

#include "../view/PutShipViewer.h"
#include "../view/BattleViewer.h"
#include "../status/GameStatus.h"

class BaseBiz {
protected:
    PutShipViewer* getPutShipViewer();
    BattleViewer* getBattleViewer();
    GameStatus* getGameStatus();

    ForceType getOtherForceType(ForceType forceType);
};


#endif //__BaseBiz_H_
