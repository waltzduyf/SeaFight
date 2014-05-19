//
// Created by 杜一飞 on 14-5-11.
//

#include "BaseUILayer.h"
#include <map>

using namespace std;

static map<int, Point> NINE_POINTS;

static int convertKey(UISideVertical v, UISideHorizontal h) {
    return v * 10 + h;
}

bool BaseUILayer::init() {
    if (!Layer::init()) {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();

    auto key = convertKey(VTop, HLeft);
    auto p = Point(0, winSize.height);
    NINE_POINTS[key] = p;

    key = convertKey(VTop, HCenter);
    p = Point(winSize.width / 2, winSize.height);
    NINE_POINTS[key] = p;

    key = convertKey(VTop, HRight);
    p = Point(winSize.width, winSize.height);
    NINE_POINTS[key] = p;

    key = convertKey(VCenter, HLeft);
    p = Point(0, winSize.height / 2);
    NINE_POINTS[key] = p;

    key = convertKey(VCenter, HCenter);
    p = Point(winSize.width / 2, winSize.height / 2);
    NINE_POINTS[key] = p;

    key = convertKey(VCenter, HRight);
    p = Point(winSize.width, winSize.height / 2);
    NINE_POINTS[key] = p;

    key = convertKey(VBottom, HLeft);
    p = Point(0, 0);
    NINE_POINTS[key] = p;

    key = convertKey(VBottom, HCenter);
    p = Point(winSize.width / 2, 0);
    NINE_POINTS[key] = p;

    key = convertKey(VBottom, HRight);
    p = Point(winSize.width, 0);
    NINE_POINTS[key] = p;

    return true;
}

void BaseUILayer::addUI(Node *node, UISideVertical v, UISideHorizontal h, float x, float y) {
    int key = convertKey(v, h);
    Point &p = NINE_POINTS[key];
    node->setPosition(p.x + x, p.y + y);
    this->addChild(node);
}
