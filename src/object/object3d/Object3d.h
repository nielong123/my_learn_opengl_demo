//
// Created by 聂龙聂龙 on 2021/8/3.
//

#ifndef TESTCPP_OBJECT3D_H
#define TESTCPP_OBJECT3D_H

#include "../../include/matrixUtil/Mat4.h"
#include "../../program/ColorShaderProgram.h"

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

    virtual void draw() {};

    void setColorShaderProgram(ColorShaderProgram colorShaderProgram) {
        _colorShaderProgram = colorShaderProgram;
    }

public:
    Mat4 mvpMatrix;

    Mat4 modelMatrix;

private:
    bool isBind;

protected:
    ColorShaderProgram _colorShaderProgram;

};


#endif //TESTCPP_OBJECT3D_H
