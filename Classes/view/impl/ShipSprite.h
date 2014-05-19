//
// Created by 杜一飞 on 14-5-10.
//


#ifndef __ShipSprite_H_
#define __ShipSprite_H_

#include "cocos2d.h"
#include "../../model/Ship.h"

USING_NS_CC;

class ShipSprite : public Node {
public:
    static ShipSprite* create(Ship *model);

    void moveToMatrixPos(const MatrixPos &pos);
    void rotateTo(RotateType t);

    void settle();

    void updateByModel();

    Ship *getModel() const {
        return model;
    }

protected:
    virtual bool init();
    Sprite *bodySprite;
    Ship *model;
    bool isSettle;
private:
};


#endif //__ShipSprite_H_
