//
// Created by 聂龙聂龙 on 2021/8/2.
//

#ifndef TESTCPP_VARYTOOLS_H
#define TESTCPP_VARYTOOLS_H

#include "../include/matrixUtil/Mat4.h"

using namespace cocos2d;


class VaryTools {

public:
    VaryTools();

    ~VaryTools() {};

private:
    Mat4 viewMatrix = Mat4::IDENTITY;
    Mat4 projectionMatrix = Mat4::IDENTITY;
    Mat4 viewProjectionMatrix = Mat4::IDENTITY;
};


#endif //TESTCPP_VARYTOOLS_H
