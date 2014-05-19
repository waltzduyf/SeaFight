//
// Created by 杜一飞 on 14-5-3.
//

#include "BattleViewer.h"

#include "../biz/BaseBiz.h"
#include "BattleBiz.h"

USING_NS_CC;

using namespace std;

BattleViewer *BattleViewer::INSTANCE = NULL;

void BattleViewer::init() {
    scene = NULL;
    enableTouch = true;
}

void BattleViewer::enter() {
    scene = Scene::create();

    // 初始化mainLayer
    Point center = getWinCenter();

    mainLayer = Layer::create();
    leftSeaPad = Sprite::create("seabg@2x.png");
    leftSeaPad->setPosition(center);
    leftSeaPad->setTag(1);
    mainLayer->addChild(leftSeaPad);

    rightSeaPad = Sprite::create("seabg@2x.png");
    rightSeaPad->setPosition(center);
    mainLayer->addChild(rightSeaPad);
    rightSeaPad->setTag(2);
    scene->addChild(mainLayer);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch *touch, Event *event)->bool{
        if (!this->enableTouch) {
            return false;
        }

        Sprite *sea = (Sprite*) event->getCurrentTarget();
        if (!sea->isVisible()) {
            return false;
        }
        Point p = sea->convertTouchToNodeSpace(touch);
        Rect seaRect;
        seaRect.size = sea->getContentSize();
        return seaRect.containsPoint(p);
    };
    touchListener->onTouchEnded = [this](Touch *touch, Event *event){
        Point p = event->getCurrentTarget()->convertTouchToNodeSpace(touch);
        MatrixPos pos = this->convertToMatrix(p);
        LOG("%d, %d", pos.first, pos.second);
        BattleBiz::getInstance()->hitMatrix(pos);
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), leftSeaPad);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), rightSeaPad);

    // 初始化UI
    uiLayer = BaseUILayer::create();
    hitCountlabel = LabelTTF::create("", FONT_FAMILY_DEFAULT, 20);
    forceTypeLabel = LabelTTF::create("", FONT_FAMILY_DEFAULT, 20);
    uiLayer->addUI(hitCountlabel, VBottom, HCenter, 0, 50);
    uiLayer->addUI(forceTypeLabel, VTop, HCenter, 0, -50);
    scene->addChild(uiLayer);

    Director::getInstance()->replaceScene(scene);
}

void BattleViewer::viewHit(MatrixPos &pos, ForceType forceType) {
    Sprite* sea = getSeaPad(forceType);

    Point p = convertToPoint(pos);
    Sprite* boom = Sprite::create("boom_hit.png");
    boom->setPosition(p);
    sea->addChild(boom);
}

void BattleViewer::viewMiss(MatrixPos &pos, ForceType forceType) {
    Sprite* sea = getSeaPad(forceType);

    Point p = convertToPoint(pos);
    Sprite* boom = Sprite::create("boom_miss.png");
    boom->setPosition(p);
    sea->addChild(boom);
}

Sprite *BattleViewer::getSeaPad(ForceType forceType) {
    return forceType == Left ? leftSeaPad : rightSeaPad;
}

void BattleViewer::viewLastHitCount(int count) {
    formatStr(hitCount, 10, "%d", count);
    hitCountlabel->setString(hitCount);
}

void BattleViewer::turnToForce(ForceType forceType) {
    leftSeaPad->setVisible(false);
    rightSeaPad->setVisible(false);

    getSeaPad(forceType)->setVisible(true);

    LOG("%d", getSeaPad(forceType)->getTag());

    string forceName = forceType == Left ? "左边" : "右边";
    forceTypeLabel->setString(forceName.c_str());
}

void BattleViewer::showWinDialog(ForceType forceType) {
    string forceName = forceType == Left ? "左边" : "右边";
    forceName += "胜利！";
    forceTypeLabel->setString(forceName.c_str());
}

void BattleViewer::showWait() {
    enableTouch = false;
}


void BattleViewer::stopWait() {
    enableTouch = true;
}
