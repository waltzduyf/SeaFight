//
// Created by 杜一飞 on 14-5-1.
//


#ifndef __SeaPad_H_
#define __SeaPad_H_

#include <string>
#include <map>
#include "Ship.h"
#include "ModelCommon.h"

enum SeaState {
    Normal, // 什么都没发生
    Miss,   // 打偏了
    Hit     // 打中了
};

class SeaPad {
public:

    SeaPad(int width, int height);

    ~SeaPad();

    int width;
    int height;

    SeaState **state;

    void setState(int x, int y, SeaState state);
    SeaState getState(int x, int y);

    void clearState();
private:
    void initState();
};


#endif //__SeaPad_H_
