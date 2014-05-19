//
// Created by 杜一飞 on 14-5-18.
//


#ifndef __Surrounder_H_
#define __Surrounder_H_

#include "../model/ModelCommon.h"

class Surrounder {
public:

    Surrounder() : round(0), count(0), preX(0), preY(0) {
    }

    MatrixPos nextPos();
private:
    int round;
    int count;

    int preX;
    int preY;
};


#endif //__Surrounder_H_
