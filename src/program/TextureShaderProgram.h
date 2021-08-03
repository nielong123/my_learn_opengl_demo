//
// Created by 聂龙聂龙 on 2021/8/2.
//

#ifndef TESTCPP_TEXTURESHADERPROGRAM_H
#define TESTCPP_TEXTURESHADERPROGRAM_H

#include <glad/glad.h>
#include "../constants/Constants.h"
#include "ShaderProgram.h"

class TextureShaderProgram : ShaderProgram {
public:
    TextureShaderProgram();

    ~TextureShaderProgram();

    void setUniforms(float matrix[], int textureId);

public :
    int uMatrixLocation;
    int uTextureUnitLocation;
    int aPositionLocation;
    int aTextureCoordinatesLocation;

private:
    inline static const char *VERTEX_SHADER = {
            "#version 100\n"
            "uniform mat4 u_Matrix;\n"
            "attribute vec4 a_Position;\n"
            "attribute vec2 a_TextureCoordinates;\n"
            "\n"
            "varying vec2 v_TextureCoordinates;\n"
            "\n"
            "void main(){\n"
            "    v_TextureCoordinates = a_TextureCoordinates;\n"
            "    gl_Position = u_Matrix * a_Position;   \n"
            "}"
    };

    inline static const char *FRAGMENT_SHADER = {
            "#version 100\n"
            "precision mediump float;\n"
            "\n"
            "uniform sampler2D u_TextureUnit;\n"
            "varying vec2 v_TextureCoordinates;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = texture2D(u_TextureUnit,v_TextureCoordinates);\n"
            "}"
    };
};


#endif //TESTCPP_TEXTURESHADERPROGRAM_H
