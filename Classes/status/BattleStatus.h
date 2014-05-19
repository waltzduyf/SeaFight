//
// Created by 杜一飞 on 14-5-18.
//


#ifndef __BattleStatus_H_
#define __BattleStatus_H_

#include "../util/CommonUtils.h"
#include "../model/ModelCommon.h"

class BattleStatus {
public:
    void init();

    int getRound() const {
        return round;
    }

    void setRound(int round) {
        BattleStatus::round = round;
    }


    int getHitCountLeft() const {
        return hitCountLeft;
    }

    void setHitCountLeft(int hitCountLeft) {
        BattleStatus::hitCountLeft = hitCountLeft;
    }

    ForceType const &getForceType() const {
        return forceType;
    }

    void setForceType(ForceType const &forceType) {
        BattleStatus::forceType = forceType;
    }

private:
    int round;
    int hitCountLeft;
    ForceType forceType;
};


#endif //__BattleStatus_H_
