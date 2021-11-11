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

    void userProgram() override;

    void deleteProgram() override;

public:
//    int aPositionLocation;
    int aMatrixLocation;
    int aColorLocation;
//    int aPointSizeLocation;

public:

    inline static const char *VERTEX_SHADER = "#version 330 core\n"
                                              "layout (location = 0) in vec4 aPos;\n"
                                              "\n"
                                              "uniform mat4 aMatrix;\n"
                                              "uniform vec3 aColor;\n"
                                              "\n"
                                              "out vec4 VColor;\n"
                                              "\n"
                                              "void main()\n"
                                              "{\n"
                                              "   gl_Position = aMatrix * aPos;\n"
                                              //   "   VColor = vec4(1.f,1.f,1.f, 1.f);\n"
                                              "   VColor = vec4(aColor, 1.f);\n"
                                              "}\n\0";


    inline static const char *FRAGMENT_SHADER = "#version 330 core\n"
                                                "\n"
                                                "out vec4 rgbColor;\n"
                                                "in vec4 VColor;\n"
                                                "\n"
                                                "void main()\n"
                                                "{\n"
                                                "   rgbColor = VColor;\n"
                                                //                                                "   rgbColor = vec4(0.9f,0.5f,0.9f,0.5f);\n"
                                                "}\n\0";
};


#endif //TESTCPP_COLORSHADERPROGRAM_H
