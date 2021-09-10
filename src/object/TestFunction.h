//
// Created by 聂龙聂龙 on 2021/9/10.
//

#ifndef TESTCPP_TESTFUNCTION_H
#define TESTCPP_TESTFUNCTION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class TestFunction {
public :
    static void testInit(unsigned int &vao, unsigned int &vbo);

    static void testInit111(const float *data, int dataLength, unsigned int &vao, unsigned int &vbo);
};


#endif //TESTCPP_TESTFUNCTION_H
