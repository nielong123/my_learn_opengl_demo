//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dCoordinateLines.h"
#include "../../helper/ColorHelper.h"


Obj3dCoordinateLines::Obj3dCoordinateLines() : Object3d() {
    Object3d();
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
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, 0xff0000);
    glDrawArrays(GL_LINES, 0, 2);

    glLineWidth(20);
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, 0x00ff00);
    glDrawArrays(GL_LINES, 2, 2);

    glLineWidth(30);
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, 0x0000ff);
    glDrawArrays(GL_LINES, 4, 2);
    glDisable(GL_DEPTH_TEST);
}



