//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __BaseUILayer_H_
#define __BaseUILayer_H_

#include "cocos2d.h"

USING_NS_CC;

enum UISideVertical {
    VTop = 0,
    VCenter,
    VBottom
};

enum UISideHorizontal {
    HLeft = 0,
    HCenter,
    HRight
};

class BaseUILayer : public Layer {
public:
    CREATE_FUNC(BaseUILayer);
    virtual bool init();

    void addUI(Node *node, UISideVertical v, UISideHorizontal h, float x, float y);
};


#endif //__BaseUILayer_H_
