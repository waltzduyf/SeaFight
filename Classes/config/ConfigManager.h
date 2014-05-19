//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __ConfigManager_H_
#define __ConfigManager_H_

#include <map>
#include <string>
#include <vector>
#include "../util/CommonUtils.h"
#include "../model/ModelCommon.h"

typedef std::map<int, int> HitCountMap;// round, hitcount
typedef std::vector<int> RoundArray;

class ConfigManager {
    SINGLETON_FUNC(ConfigManager);
public:
    ShipMap& getShipModels();
    int getHitCountByRound(int round);
private:
    ShipMap shipMap;
    void initShip();
    void addShipPrototype(Ship *ship);

    HitCountMap hitCountMap;
    RoundArray roundArray;
    void initHitCount();
    void addHitCountConfig(int round, int hitCount);
};


#endif //__ConfigManager_H_
