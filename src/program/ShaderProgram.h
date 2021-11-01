//
// Created by 聂龙聂龙 on 2021/7/30.
//

#ifndef TESTCPP_SHADERPROGRAM_H
#define TESTCPP_SHADERPROGRAM_H


class ShaderProgram {
public :
    ShaderProgram(const char *VERTEX_SHADER, const char *FRAGMENT_SHADER);

    virtual void userProgram();

    virtual void deleteProgram();

    int getProgramId();

    int programId;
private:

};


#endif //TESTCPP_SHADERPROGRAM_H
