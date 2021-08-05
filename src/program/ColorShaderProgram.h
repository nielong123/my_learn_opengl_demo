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
//    inline static const char *VERTEX_SHADER = R"GLSL(#version 330 core
//                                                    layout (location = 0) in vec3 aPos;
//                                                    void main()
//                                                    {
//                                                       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//                                                    })GLSL";
    inline static const char *VERTEX_SHADER = R"GLSL(#version 330 core
                                               layout(location = 0)in vec4 a_Position;
                                               uniform mat4 u_Matrix;
                                               uniform float m_pointSize;
                                               in vec4 u_Color;

                                               void main()
                                               {
                                                   gl_PointSize = m_pointSize;
                                                   gl_Position = u_Matrix * a_Position;
                                               })GLSL";


//    inline static const char *FRAGMENT_SHADER = R"GLSL(#version 330 core
//                                                    out vec4 FragColor;
//
//                                                    void main()
//                                                    {
//                                                        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//                                                    })GLSL";
    inline static const char *FRAGMENT_SHADER = R"GLSL(#version 330 core
                                                 vec4 u_Color;
                                                 out vec4 fragColor;
                                                 void main()
                                                 {
                                                     fragColor = u_Color;
                                                 })GLSL";
};


#endif //TESTCPP_COLORSHADERPROGRAM_H
