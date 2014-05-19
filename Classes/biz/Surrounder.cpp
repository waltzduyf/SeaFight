//
// Created by 杜一飞 on 14-5-18.
//

#include "Surrounder.h"


//MatrixPos Surrounder::nextPos() {
//    int dia = 3 + round * 2;
//    int x, y;
//    if (count < dia - 1) {
//        x = -(round) + count;
//        y = round + 1;
//    } else if (count < 2 * dia - 2) {
//        int dCount = count % (1 * dia - 1);
//        x = round + 1;
//        y = round - dCount;
//    } else if (count < 3 * dia - 3) {
//        int dCount = count % (2 * dia - 2);
//        x = round - dCount;
//        y = -round - 1;
//    } else if (count < 4 * dia - 4) {
//        int dCount = count % (3 * dia - 3);
//        x = -round - 1;
//        y = -round + dCount;
//    } else {
//        round++;
//        count = 0;
//        return nextPos();
//    }
//
//    count++;
//
//    return MatrixPos(x, y);
//}

MatrixPos Surrounder::nextPos() {
    int dia = 3 + round * 2;
    int x, y;
    if (count == 0) {
        x = 0;
        y = 1;
    } else if (count < dia - 1) {
        x = 1;
        y = 0;
    } else if (count < 2 * dia - 2) {
        x = 0;
        y = -1;
    } else if (count < 3 * dia - 3) {
        x = -1;
        y = 0;
    } else if (count < 4 * dia - 4) {
        x = 0;
        y = 1;
    } else {
        round++;
        count = 0;
        return nextPos();
    }

    count++;

    return MatrixPos(x, y);
}
