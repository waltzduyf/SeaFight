//
// Created by 杜一飞 on 14-5-1.
//


#ifndef __CommonUtils_H_
#define __CommonUtils_H_

#include <string>
#include "cocos2d.h"

#define fori(i, min, max) \
for (auto i = min; i < max; i++)

#define foreach(it, col, type) \
for (auto it = (col).begin(); it != (col).end(); it++)

#define SINGLETON_FUNC(type) \
public: \
    static type* getInstance() { \
        if (INSTANCE == NULL) { \
            INSTANCE = new type(); \
            INSTANCE->init(); \
        } \
        return INSTANCE; \
    } \
private: \
    void init(); \
    static type *INSTANCE;

#define LOG(...) cocos2d::log(__VA_ARGS__)

#define formatStr(str, bufferSize, ptnStr, ...) \
char str[bufferSize]; \
sprintf(str, ptnStr, __VA_ARGS__);

class CommonUtils {
public:
};


#endif //__CommonUtils_H_
