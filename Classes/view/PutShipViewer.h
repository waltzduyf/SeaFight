//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __PutShipViewer_H_
#define __PutShipViewer_H_

#include "../util/CommonUtils.h"
#include "../model/ModelCommon.h"
#include "../model/Ship.h"
#include "impl/BaseUILayer.h"
#include "impl/ShipSprite.h"
#include "cocos2d.h"
#include "UIButton.h"
#include "BaseViewer.h"

using namespace cocos2d::ui;

class PutShipViewer : public BaseViewer {
    SINGLETON_FUNC(PutShipViewer);
public:
    void intoScene();

    void initSea();

    void putInShip(Ship *ship);

    void moveShip(Ship *ship);
    void rotateTo(Ship *ship, RotateType rotateType);

    void showForceType(ForceType forceType);

    void settleShip(Ship *ship);
private:
    Scene *scene;
    Layer *mainLayer;
    BaseUILayer *uiLayer;
    LabelTTF *label;
    Sprite *seaPad;

    ShipSprite* getShipSprite(int shipId);

    void onSettleButtonClick(Ref*,TouchEventType);
};


#endif //__PutShipViewer_H_
