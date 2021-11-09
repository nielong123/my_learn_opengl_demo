//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include "Obj3dPoint.h"

Obj3dPoint::Obj3dPoint(float x, float y, float z, int color) {
    vertexData[0] = x;
    vertexData[1] = y;
    vertexData[2] = z;
    this->color = color;
    Obj3dPoint();
}

Obj3dPoint::Obj3dPoint(float x, float y, float z) {
    Obj3dPoint(x, y, z, 0xf234f6);
}

Obj3dPoint::Obj3dPoint() : Object3d() {
    _VertexArray = new VertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData), vao, vbo);
}

Obj3dPoint::~Obj3dPoint() {

}

void Obj3dPoint::draw() {
    Object3d::draw();
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);

    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setColor(color);
    glPointSize(30);
    glDrawArrays(GL_POINTS, 0, 1);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

void Obj3dPoint::bind() {


}

void Obj3dPoint::unbind() {


}
