//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include "Obj3dPoint.h"
#include "../../helper/ColorHelper.h"

Obj3dPoint::Obj3dPoint(float x, float y, float z, int color) : Object3d() {
    vertexData[0] = x;
    vertexData[1] = y;
    vertexData[2] = z;
    rgbColor = color;
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dPoint::Obj3dPoint(float x, float y, float z) : Object3d() {
    vertexData[0] = x;
    vertexData[1] = y;
    vertexData[2] = z;
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dPoint::Obj3dPoint() : Object3d() {
    rgbColor = 0xf234f6;
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dPoint::~Obj3dPoint() {
}

void Obj3dPoint::draw() {
    Object3d::draw();
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, rgbColor);

    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(30);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void Obj3dPoint::bind() {
    Object3d::bind();
}

void Obj3dPoint::unbind() {
    Object3d::unbind();
    _colorShaderProgram.deleteProgram();
    glDisableVertexAttribArray(0);
}
