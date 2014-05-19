//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __PutShipBiz_H_
#define __PutShipBiz_H_

#include "../util/CommonUtils.h"
#include "../model/ModelCommon.h"
#include "BaseBiz.h"
#include "../model/Force.h"
#include "../status/PutShipStatus.h"

class PutShipBiz : public BaseBiz {
    SINGLETON_FUNC(PutShipBiz);
public:
    void enter();
    void moveCurrentShipTo(const MatrixPos &pos);
    void switchRotation();
    void settleAndPutNext();

protected:
    PutShipStatus* getPutShipStatus();
private:
    Ship* putInNextShip();
    Ship* createNextShip();
    Ship* createFromPrototype(std::string type);
    int generateShipId();
    void switchToNextForce();

    Force *getCurrentForce();

    bool isOut(Ship *curShip, RotateType rotateType, const MatrixPos &pos);
    bool isOverlapping(Ship *curShip, RotateType rotateType, const MatrixPos &pos);
};


#endif //__PutShipBiz_H_
