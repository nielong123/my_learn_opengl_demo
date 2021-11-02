//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dTriangle.h"


Obj3dTriangle::Obj3dTriangle() : Object3d() {
    _VertexArray = new VertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData), vao, vbo);
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
    glEnableVertexAttribArray(0);
    glUniform3f(_colorShaderProgram.aColorLocation, 0.3f, 1.0f, 1.f);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



