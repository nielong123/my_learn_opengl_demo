//
// Created by 聂龙聂龙 on 2021/7/30.
//

#include <glad/glad.h>
#include <cstdio>
#include "ColorShaderProgram.h"
#include "../constants/Constants.h"

ColorShaderProgram::ColorShaderProgram() :
        ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER) {
    glUseProgram(programId);
//    aPositionLocation = glGetAttribLocation(programId, Constants::A_POSITION);
    aMatrixLocation = glGetUniformLocation(programId, Constants::A_MATRIX);
    aColorLocation = glGetUniformLocation(programId, Constants::A_COLOR);
//    aPointSizeLocation = glGetUniformLocation(programId, Constants::A_POINTSIZE);
}

ColorShaderProgram::~ColorShaderProgram() {

}

void ColorShaderProgram::userProgram() {
    ShaderProgram::userProgram();
}

void ColorShaderProgram::deleteProgram() {
    ShaderProgram::deleteProgram();
}
