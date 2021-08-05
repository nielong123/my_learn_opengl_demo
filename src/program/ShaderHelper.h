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

    int compileVertexShader(const char *strSharer);

    int compileFragmentShader(const char *strSharer);

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
    bool validateProgram(int programId);

};


#endif //TESTCPP_SHADERHELPER_H
