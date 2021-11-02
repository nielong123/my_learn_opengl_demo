//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dCoordinateLines.h"


Obj3dCoordinateLines::Obj3dCoordinateLines() : Object3d() {
    _VertexArray = new VertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData), vao, vbo);
}

Obj3dCoordinateLines::~Obj3dCoordinateLines() {

}

void Obj3dCoordinateLines::unbind() {
    Object3d::unbind();
    glDisableVertexAttribArray(0);
}


void Obj3dCoordinateLines::bind() {
    Object3d::bind();
}

void Obj3dCoordinateLines::draw() {
    Object3d::draw();
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);

    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(10);
    glUniform3f(_colorShaderProgram.aColorLocation, 1.f, 0.0f, 0.f);
    glDrawArrays(GL_LINES, 0, 2);

    glLineWidth(20);
    glUniform3f(_colorShaderProgram.aColorLocation, 0.f, 1.0f, 0.f);
    glDrawArrays(GL_LINES, 2, 2);

    glLineWidth(30);
    glUniform3f(_colorShaderProgram.aColorLocation, 0.f, 0.0f, 1.f);
    glDrawArrays(GL_LINES, 4, 2);
    glDisable(GL_DEPTH_TEST);
}



