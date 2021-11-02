//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dTriangle.h"
#include <iostream>


Obj3dTriangle::Obj3dTriangle() : Object3d() {
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
    glUniform3f(_colorShaderProgram.aColorLocation, color[0], color[1], color[2]);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);

    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisable(GL_DEPTH_TEST);
}

void Obj3dTriangle::setColor(int hexRGBColor) {
    this->color[0] = float(hexRGBColor >> 16 & 0xff) / 0xff;
    this->color[1] = float(hexRGBColor >> 8 & 0xff) / 0xff;
    this->color[2] = float(hexRGBColor & 0xff) / 0xff;
}



