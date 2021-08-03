
//
// Created by 聂龙聂龙 on 2021/8/2.
//

#include "TextureShaderProgram.h"

TextureShaderProgram::TextureShaderProgram()
        : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER) {
    uMatrixLocation = glGetUniformLocation(programId, Constants::U_MATRIX);
    uTextureUnitLocation = glGetUniformLocation(programId, Constants::U_TEXTURE_UNIT);
    aPositionLocation = glGetAttribLocation(programId, Constants::A_POSITION);
    aTextureCoordinatesLocation = glGetAttribLocation(programId, Constants::A_TEXTURE_COORDINATES);
}

void TextureShaderProgram::setUniforms(float matrix[], int textureId) {
    // 传入变化矩阵到shaderProgram
    glUniformMatrix4fv(uMatrixLocation, 1, false, matrix);
//        //激活纹理单元0
    glActiveTexture(GL_TEXTURE0);
    //绑定纹理对象ID
    glBindTexture(GL_TEXTURE_2D, textureId);
    //告诉shaderProgram sampler 2d纹理采集器，使用纹理单元0的纹理对象
    glUniform1i(uTextureUnitLocation, 0);
}
