//
// Created by 聂龙聂龙 on 2021/7/30.
//

#ifndef TESTCPP_COLORSHADERPROGRAM_H
#define TESTCPP_COLORSHADERPROGRAM_H


#include "ShaderProgram.h"

class ColorShaderProgram : ShaderProgram {
public:
    ColorShaderProgram();

    ~ColorShaderProgram();

    void userProgram();

public:
    int aPositionLocation;
    int aMatrixLocation;
    int aColorLocation;
    int aPointSizeLocation;

public:

    inline static const char *VERTEX_SHADER = "#version 330 core\n"
                                              "layout (location = 0) in vec3 aPos;\n"
                                              "uniform mat4 aMatrix;"
                                              "\n"
                                              "void main()\n"
                                              "{\n"
                                              "   gl_Position = aMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                              "}\0";


    inline static const char *FRAGMENT_SHADER = "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "uniform vec4 aColor;\n"
                                                "\n"
                                                "in vec4 outColor;\n"
                                                "\n"
                                                "void main()\n"
                                                "{\n"
                                                "   FragColor = aColor;\n"
                                                "}\0";
};


#endif //TESTCPP_COLORSHADERPROGRAM_H
