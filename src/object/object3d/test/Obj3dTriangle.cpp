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
}

void Obj3dTriangle::bind() {
    Object3d::bind();

    glVertexAttribPointer(_colorShaderProgram.aPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Obj3dTriangle::draw() {
    Object3d::draw();
    _colorShaderProgram.userProgram();
    glUniform4f(_colorShaderProgram.aColorLocation, 0.3f, 1.0f, 1.f, 0.3f);

    Mat4 testmatrix = Mat4::IDENTITY;
    testmatrix.translate(0.1f, 0.0f, 0.0f);
//    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, Mat4::IDENTITY.m);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, testmatrix.m);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



