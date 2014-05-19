//
// Created by 杜一飞 on 14-5-18.
//

#include "BaseViewer.h"

MatrixPos BaseViewer::convertToMatrix(const Point &p) {
    int x = 0, y = 0;
    float fx = p.x, fy = p.y;

    x = fx / SEA_PAD_PICE_SIZE;
    y = fy / SEA_PAD_PICE_SIZE;

    return MatrixPos(x, y);
}

Point BaseViewer::getWinCenter() {
    auto wins = Director::getInstance()->getWinSize();

    return Point(wins.width / 2 , wins.height / 2);
}

Point BaseViewer::convertToPoint(MatrixPos &pos) {
    float x = pos.first * SEA_PAD_PICE_SIZE + SEA_PAD_PICE_SIZE / 2;
    float y = pos.second * SEA_PAD_PICE_SIZE + SEA_PAD_PICE_SIZE / 2;
    return cocos2d::Point(x, y);
}
