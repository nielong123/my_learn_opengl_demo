//
// Created by 聂龙聂龙 on 2021/8/3.
//

#ifndef TESTCPP_OBJECT3D_H
#define TESTCPP_OBJECT3D_H

#include "../../include/matrixUtil/Mat4.h"
#include "../../program/ColorShaderProgram.h"
#include "../../arrays/VertexArray.h"

using namespace cocos2d;

class Object3d {

public:

    Object3d() {
        mvpMatrix = Mat4::IDENTITY;
        modelMatrix = Mat4::IDENTITY;
    };

    virtual ~Object3d() {};

    virtual void bind() { isBind = true; };

    virtual void unbind() {};

    void draw(const Mat4 viewProjectMatrix) {
        if (!isBind) {
            bind();
        }
        Mat4::multiply(viewProjectMatrix, modelMatrix, &mvpMatrix);
        draw();
        unbind();
    }

    void drawTest() {
        if (!isBind) {
            bind();
        }
        draw();
        unbind();
    }

    virtual void draw() {};

    void setColorShaderProgram(ColorShaderProgram colorShaderProgram) {
        _colorShaderProgram = colorShaderProgram;
    }

public:

    VertexArray *_VertexArray;

    Mat4 mvpMatrix;

    Mat4 modelMatrix;

    GLuint vao;
    GLuint vbo;

private:
    bool isBind;

protected:
    ColorShaderProgram _colorShaderProgram;

    void setColor(int hexRGBColor) {
        float color[3];
        color[0] = float(hexRGBColor >> 16 & 0xff) / 0xff;
        color[1] = float(hexRGBColor >> 8 & 0xff) / 0xff;
        color[2] = float(hexRGBColor & 0xff) / 0xff;
        glUniform3f(_colorShaderProgram.aColorLocation, color[0], color[1], color[2]);
    }
};


#endif //TESTCPP_OBJECT3D_H
