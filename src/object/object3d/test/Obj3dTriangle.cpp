//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dTriangle.h"
#include "../../../helper/ColorHelper.h"
#include <iostream>


Obj3dTriangle::Obj3dTriangle() : Object3d() {
    Object3d();
    _VertexArray = new VertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData), vao, vbo);
}

Obj3dTriangle::~Obj3dTriangle() {

}

void Obj3dTriangle::unbind() {
    Object3d::unbind();
    glDisableVertexAttribArray(0);
}

void Obj3dTriangle::bind() {
    Object3d::bind();

}

void Obj3dTriangle::draw() {
    Object3d::draw();
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, fillColor);
    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisable(GL_DEPTH_TEST);
}

void Obj3dTriangle::setFillColor(int hexRGBColor) {
    this->fillColor = hexRGBColor;
}



