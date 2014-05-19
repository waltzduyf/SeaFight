//
// Created by 杜一飞 on 14-5-10.
//

#include "ShipSprite.h"
#include "../../util/CommonUtils.h"
#include "../ViewConsts.h"
#include "../../biz/PutShipBiz.h"

ShipSprite *ShipSprite::create(Ship *model) {
    auto ret = new ShipSprite;
    ret->model = model;

    Sprite *body = Sprite::create("ship@2x.png");

    // 计算一下伸缩
    float scaleX = (float) model->length / 4;
    body->setScaleX(scaleX);

    ret->addChild(body);
    float anchorPointX = (double) SEA_PAD_PICE_SIZE_HALF / (model->length * SEA_PAD_PICE_SIZE);
    body->setAnchorPoint(Point(anchorPointX, 0.5));
    body->setPosition(SEA_PAD_PICE_SIZE_HALF, SEA_PAD_PICE_SIZE_HALF);
    ret->bodySprite = body;

    ret->isSettle = false;

    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}

bool ShipSprite::init() {

    if (!Node::init()) {
        return false;
    }

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this](Touch *touch, Event *event)->bool{
        if (isSettle) {
            return false;
        }

        Point touchP = this->bodySprite->convertTouchToNodeSpace(touch);
        Rect bb;
        bb.size = this->bodySprite->getContentSize();

        return bb.containsPoint(touchP);
    };
    touchListener->onTouchEnded = [this](Touch *touch, Event *event)->void{
        PutShipBiz::getInstance()->switchRotation();
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    this->updateByModel();

    return true;
}

void ShipSprite::moveToMatrixPos(const MatrixPos &pos) {
    float x = pos.first * SEA_PAD_PICE_SIZE;
    float y = pos.second * SEA_PAD_PICE_SIZE;
    this->setPosition(x, y);
}


void ShipSprite::rotateTo(RotateType t) {
    float angle = t == Vertical ? 90 : 0;
    bodySprite->setRotation(angle);
}

void ShipSprite::updateByModel() {
    rotateTo(model->rotateType);
    moveToMatrixPos(model->pos);
}

void ShipSprite::settle() {
    isSettle = true;
}
