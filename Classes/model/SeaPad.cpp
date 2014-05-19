//
// Created by 杜一飞 on 14-5-1.
//

#include "SeaPad.h"

#include "../util/CommonUtils.h"

SeaPad::SeaPad(int width, int height) : width(width), height(height) {
    state = new SeaState*[width];
    initState();
}

SeaPad::~SeaPad() {
}

void SeaPad::initState() {
    fori(i, 0, width) {
        state[i] = new SeaState[height];
        *(state[i]) = {Normal};
    }
}

void SeaPad::setState(int x, int y, SeaState state) {
    this->state[x][y] = state;
}


SeaState SeaPad::getState(int x, int y) {
    return state[x][y];
}

void SeaPad::clearState() {
    initState();
}
