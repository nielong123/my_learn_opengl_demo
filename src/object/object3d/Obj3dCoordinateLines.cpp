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
}


void Obj3dCoordinateLines::bind() {
    Object3d::bind();
}

void Obj3dCoordinateLines::draw() {
    Object3d::draw();
//    _colorShaderProgram.userProgram();
    glBindVertexArray(vao);
//    glLineWidth(10);
//    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDisable(GL_DEPTH_TEST);
//    printf("draw coordinateLines \n");
}



