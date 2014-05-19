//
// Created by 杜一飞 on 14-5-11.
//

#include "PutShipViewer.h"
#include "ViewConsts.h"
#include "../biz/PutShipBiz.h"

PutShipViewer *PutShipViewer::INSTANCE = NULL;

void PutShipViewer::init() {
    mainLayer = NULL;
    uiLayer = NULL;
}


void PutShipViewer::intoScene() {
    scene = Scene::create();

    auto wins = Director::getInstance()->getWinSize();

    uiLayer = BaseUILayer::create();
    uiLayer->setLocalZOrder(ZORDER_UI_LAYER);
    scene->addChild(uiLayer);

    // 确认按钮
    Button *button = Button::create("button.png", "buttonHighlighted.png", "button.png");
    button->setTitleText("放置!");
    button->setPosition(Point(wins.width / 2, 50));
    button->setScale9Enabled(true);
    button->setTitleFontSize(18);
    button->setTitleFontName(FONT_FAMILY_DEFAULT);
    button->setSize(Size(100, 50));
    button->addTouchEventListener(this, toucheventselector(PutShipViewer::onSettleButtonClick));
    uiLayer->addUI(button, VBottom, HCenter, 0, 50);

    // 标题
    label = LabelTTF::create("", FONT_FAMILY_DEFAULT, 24);
    uiLayer->addUI(label, VTop, HCenter, 0, -50);

    if (Director::getInstance()->getRunningScene() != NULL) {
        Director::getInstance()->replaceScene(scene);
    } else {
        Director::getInstance()->runWithScene(scene);
    }
}

void PutShipViewer::initSea() {

    if (mainLayer != NULL) {
        scene->removeChild(mainLayer);
    }

    mainLayer = Layer::create();
    mainLayer->setLocalZOrder(ZORDER_MAIN_LAYER);
    scene->addChild(mainLayer);

    // 海面
    auto wins = Director::getInstance()->getWinSize();

    float topLeftX = (wins.width - SEA_PAD_PICE_SIZE * SEA_PAD_PICE_ROW) / 2;
    float topLeftY = (wins.height - SEA_PAD_PICE_SIZE * SEA_PAD_PICE_ROW) / 2 + SEA_PAD_PICE_SIZE * SEA_PAD_PICE_ROW;

    LOG("%f,%f", topLeftX, topLeftY);

    seaPad = Sprite::create("seabg@2x.png");
    seaPad->setPosition(topLeftX, topLeftY);
    seaPad->setAnchorPoint(Point(0, 1));
    mainLayer->addChild(seaPad);
    seaPad->setLocalZOrder(ZORDER_SEAPAD);
    auto sea = seaPad;

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this, sea](Touch *touch, Event *event){
        Point p = sea->convertTouchToNodeSpace(touch);
        Rect seaRect = Rect(0, 0, sea->getContentSize().width, sea->getContentSize().height);
        return seaRect.containsPoint(p);
    };
    touchListener->onTouchEnded = [this](Touch *touch, Event *event){
        Point touchP = event->getCurrentTarget()->convertTouchToNodeSpace(touch);
        MatrixPos pos = this->convertToMatrix(touchP);
        LOG("%d, %d", pos.first, pos.second);
        PutShipBiz::getInstance()->moveCurrentShipTo(pos);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, seaPad);
}

static int convertToShipTag(int shipId) {
    return 1000 + shipId;
}

void PutShipViewer::putInShip(Ship *ship) {
    auto shipSprite = ShipSprite::create(ship);
    shipSprite->setTag(convertToShipTag(ship->id));
    shipSprite->setLocalZOrder(ZORDER_SHIP);
    seaPad->addChild(shipSprite);
}

ShipSprite *PutShipViewer::getShipSprite(int shipId) {
    int tag = convertToShipTag(shipId);
    auto shipSprite = (ShipSprite*) seaPad->getChildByTag(tag);
    return shipSprite;
}

void PutShipViewer::moveShip(Ship *ship) {
    auto shipSprite = getShipSprite(ship->id);
    shipSprite->moveToMatrixPos(ship->pos);
}

void PutShipViewer::rotateTo(Ship *ship, RotateType rotateType) {
    auto shipSprite = getShipSprite(ship->id);
    shipSprite->rotateTo(ship->rotateType);
}

void PutShipViewer::onSettleButtonClick(Ref *ptr, TouchEventType type) {
    Button *b = (Button*) ptr;
    if (type == TOUCH_EVENT_BEGAN) {
        b->setSize(Size(120, 60));
    } else if (type == TOUCH_EVENT_ENDED) {
        b->setSize(Size(100, 50));
        PutShipBiz::getInstance()->settleAndPutNext();
    }
}

void PutShipViewer::showForceType(ForceType forceType) {
    string forceName = forceType == Left ? "左边" : "右边";
    forceName += "阵营\n请放置一艘军舰";
    label->setString(forceName.c_str());
}

void PutShipViewer::settleShip(Ship *ship) {
    auto shipSprite = getShipSprite(ship->id);
    shipSprite->settle();
}
