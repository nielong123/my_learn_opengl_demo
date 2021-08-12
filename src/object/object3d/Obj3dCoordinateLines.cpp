//
// Created by 聂龙聂龙 on 2021/8/5.
//

#include "Obj3dCoordinateLines.h"


Obj3dCoordinateLines::Obj3dCoordinateLines() : Object3d() {
    _VertexArray = new VertexArray(vertexData);

}

Obj3dCoordinateLines::~Obj3dCoordinateLines() {

}

void Obj3dCoordinateLines::unbind() {
    Object3d::unbind();
}

void Obj3dCoordinateLines::draw() {
    Object3d::draw();
    _colorShaderProgram.userProgram();
    printf("draw coordinateLines \n");
}

void Obj3dCoordinateLines::bind() {
    Object3d::bind();
    _VertexArray->enableVertexAttributePointer(_colorShaderProgram.aPositionLocation, 2, 0);
}

//void Obj3dCoordinateLines::setColorShaderProgram(ColorShaderProgram _ColorShaderProgram) {
//    Object3d::setColorShaderProgram(_ColorShaderProgram);
//}


