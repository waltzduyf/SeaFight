//
// Created by 杜一飞 on 14-5-18.
//


#ifndef __BaseViewer_H_
#define __BaseViewer_H_

#include "../model/ModelCommon.h"
#include "ViewConsts.h"
#include "cocos2d.h"
#include "impl/BaseUILayer.h"

USING_NS_CC;

class BaseViewer : public Ref {
protected:
    MatrixPos convertToMatrix(const Point &p);
    Point convertToPoint(MatrixPos &pos);
    Point getWinCenter();
};


#endif //__BaseViewer_H_
