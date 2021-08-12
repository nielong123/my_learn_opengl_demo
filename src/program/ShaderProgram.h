//
// Created by 聂龙聂龙 on 2021/7/30.
//

#ifndef TESTCPP_SHADERPROGRAM_H
#define TESTCPP_SHADERPROGRAM_H


class ShaderProgram {
public :
    ShaderProgram(const char *VERTEX_SHADER, const char *FRAGMENT_SHADER);

    virtual void userProgram();

protected:
    int programId;
};


#endif //TESTCPP_SHADERPROGRAM_H
