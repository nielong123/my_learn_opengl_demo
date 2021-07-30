//
// Created by 聂龙聂龙 on 2021/7/30.
//

#include "ShaderProgram.h"
#include "ShaderHelper.h"

ShaderProgram::ShaderProgram(const char *VERTEX_SHADER, const char *FRAGMENT_SHADER) {
    ShaderHelper *_ShaderHelper = new ShaderHelper();
    programId = _ShaderHelper->buildProgram(VERTEX_SHADER, FRAGMENT_SHADER);
}
