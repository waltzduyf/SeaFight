//
// Created by 杜一飞 on 14-5-3.
//


#ifndef __BattleViewer_H_
#define __BattleViewer_H_

#include "cocos2d.h"
#include "../util/CommonUtils.h"

#include "BaseViewer.h"
#include "../model/ModelCommon.h"

class BattleViewer : public BaseViewer {
    SINGLETON_FUNC(BattleViewer)
public:
    // 进入
    void enter();
    void viewHit(MatrixPos &pos, ForceType forceType);
    void viewMiss(MatrixPos &pos, ForceType forceType);
    void viewLastHitCount(int count);
    void turnToForce(ForceType forceType);
    void showWinDialog(ForceType forceType);

    void showWait();
    void stopWait();
private:
    Scene *scene;
    Layer *mainLayer;
    BaseUILayer *uiLayer;
    Sprite *leftSeaPad;
    Sprite *rightSeaPad;

    LabelTTF *hitCountlabel;
    LabelTTF *forceTypeLabel;

    bool enableTouch;

    Sprite* getSeaPad(ForceType forceType);
};


#endif //__BattleViewer_H_
