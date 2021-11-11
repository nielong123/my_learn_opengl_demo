//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dTriangle.h"
#include "../../helper/ColorHelper.h"
#include "../../constants/GlobalsDefine.h"
#include <iostream>


Obj3dTriangle::Obj3dTriangle() : Object3d() {
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dTriangle::Obj3dTriangle(Point &point1, Point &point2, Point &point3, int hexColor) : Object3d() {
    vertexData[0] = point1.x;
    vertexData[1] = point1.y;
    vertexData[2] = point1.z;
    vertexData[3] = point2.x;
    vertexData[4] = point2.y;
    vertexData[5] = point2.z;
    vertexData[6] = point3.x;
    vertexData[7] = point3.y;
    vertexData[8] = point3.z;
    fillColor = hexColor;
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dTriangle::~Obj3dTriangle() {

}

void Obj3dTriangle::unbind() {
    Object3d::unbind();
    glDisableVertexAttribArray(0);
    _colorShaderProgram.deleteProgram();
}

void Obj3dTriangle::bind() {
    Object3d::bind();
}

void Obj3dTriangle::draw() {
    Object3d::draw();
    _colorShaderProgram.userProgram();
    GL_CHECK_ERROR(glEnableVertexAttribArray(0));
    GL_CHECK_ERROR(glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m));
    GL_CHECK_ERROR(ColorHelper::setColor(_colorShaderProgram.aColorLocation, fillColor));
    GL_CHECK_ERROR(glBindVertexArray(vao));
    GL_CHECK_ERROR(glEnable(GL_DEPTH_TEST));
    GL_CHECK_ERROR(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK_ERROR(glDisable(GL_DEPTH_TEST));
}

void Obj3dTriangle::setFillColor(int hexRGBColor) {
    this->fillColor = hexRGBColor;
}
