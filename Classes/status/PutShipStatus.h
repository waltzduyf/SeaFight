//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __PutShipStatus_H_
#define __PutShipStatus_H_

#include <string>
#include "../model/ModelCommon.h"
#include "../model/Force.h"

class PutShipStatus {
public:
    void init();

    ForceType currentForceType;
    std::string currentShipType;

    Force* getCurrentForce();
    Ship* getCurrentShip();
};


#endif //__PutShipStatus_H_
