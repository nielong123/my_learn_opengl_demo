//
// Created by 聂龙聂龙 on 2021/11/9.
//

#include <glad/glad.h>

#ifndef TESTCPP_COLORHELPER_H
#define TESTCPP_COLORHELPER_H

class ColorHelper {
public:
    static void setColor(int &colorId, int hexRGBColor) {
        float color[3];
        color[0] = float(hexRGBColor >> 16 & 0xff) / 0xff;
        color[1] = float(hexRGBColor >> 8 & 0xff) / 0xff;
        color[2] = float(hexRGBColor & 0xff) / 0xff;
        glUniform3f(colorId, color[0], color[1], color[2]);
    }
};

#endif //TESTCPP_COLORHELPER_H
