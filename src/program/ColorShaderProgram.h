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

private:
    int aPositionLocation;
    int aMatrixLocation;
    int aColorLocation;
    int aPointSizeLocation;

private:
    inline static const char *VERTEX_SHADER = {"#version 330\n"
                                               "in vec4 a_Position;"
                                               "in vec2 a_TexCoordinate;"
                                               "uniform mat4 u_Matrix;"
                                               "uniform float m_pointSize;"
                                               ""
                                               "void main()"
                                               "{"
                                               "    gl_PointSize = m_pointSize;"
                                               "    gl_Position = u_Matrix * a_Position;"
                                               "}"
    };

    inline static const char *FRAGMENT_SHADER = {"#version 330\n"
//                                                 "precision mediump float;"
                                                 "uniform vec4 u_Color;\n"

                                                 "out vec4 fragColor;\n"

                                                 "void main()"
                                                 "{"
                                                 "    fragColor = u_Color;"
                                                 "}"
    };
};


#endif //TESTCPP_COLORSHADERPROGRAM_H
