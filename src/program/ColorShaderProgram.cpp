//
// Created by 聂龙聂龙 on 2021/7/30.
//

#include <glad/glad.h>
#include "ColorShaderProgram.h"
#include "../constants/Constants.h"

ColorShaderProgram::ColorShaderProgram() :
        ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER) {
    glUseProgram(programId);
    aMatrixLocation = glGetUniformLocation(programId, Constants::U_MATRIX);
    aPositionLocation = glGetAttribLocation(programId, Constants::A_POSITION);
    aColorLocation = glGetUniformLocation(programId, Constants::A_COLOR);
    aPointSizeLocation = glGetUniformLocation(programId, Constants::A_POINTSIZE);
}

ColorShaderProgram::~ColorShaderProgram() {

}
