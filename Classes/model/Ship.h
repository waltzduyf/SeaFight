//
// Created by 杜一飞 on 14-5-1.
//


#ifndef __Ship_H_
#define __Ship_H_

#include <string>
#include "ModelCommon.h"

class Ship {
public:
    int id;
    std::string type;
    int length;
    bool *health; // 健康数组，true是健康，false是损坏
    RotateType rotateType;
    MatrixPos pos;

    Ship(int id, const std::string &type, int length);
    ~Ship();

    void setHealth(int pos, bool isHealth);
    bool isDestroy();
};


#endif //__Ship_H_
