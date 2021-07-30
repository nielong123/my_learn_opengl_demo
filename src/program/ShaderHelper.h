//
// Created by 聂龙聂龙 on 2021/7/26.
//

#ifndef TESTCPP_SHADERHELPER_H
#define TESTCPP_SHADERHELPER_H


#include <string>

class ShaderHelper {
public:
    int buildProgram(const char *vertex_sharer, const char *fragment_sharer);

    int linkProgram(int vertexShader, int fragmentShader);

protected:
    int programId;

    int compileVertexShader(const char *vertex_sharer);

    int compileFragmentShader(const char *fragment_sharer);

    /***
     * 将glsl和读取成着色器程序
     * @param type
     * @param glsl
     * @return
     */
    int compileShader(int type, const char *glsl);

    /***
     * 验证程序是否可用
     * @param vertex_sharer
     * @return
     */
    void validateProgram();

    const char *STR_VERTEX_SHADER = R"GLSL(
        #version 100
        attribute vec4 a_Position;
        attribute vec2 a_TexCoordinate;
        uniform mat4 u_Matrix;
        uniform float m_pointSize;

        void main()
        {
            gl_PointSize = m_pointSize;
        //    gl_PointSize = 32.0;
            gl_Position = u_Matrix * a_Position;
        }
    )GLSL";
};


#endif //TESTCPP_SHADERHELPER_H
