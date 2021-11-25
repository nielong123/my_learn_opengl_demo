//
// Created by 聂龙聂龙 on 2021/11/24.
//

#include "Obj3dPolyLine.h"
#include "../../helper/ColorHelper.h"


Obj3dPolyLine::Obj3dPolyLine(const Polyline polyline) : Object3d() {
    this->polyline = polyline;
    vector<const Point *> vector = this->polyline.getAllPoints();
    float vertexData[vector.size() * 3];
    int index = 0;
    for (int i = 0; i < vector.size(); ++i) {
        Point *point = const_cast<Point *>(vector[i]);
        vertexData[index++] = point->x;
        vertexData[index++] = point->y;
        vertexData[index++] = point->z;
    }
    getVertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData));
}

Obj3dPolyLine::Obj3dPolyLine() : Object3d() {

}

void Obj3dPolyLine::draw() {
    Object3d::draw();
    _colorShaderProgram.userProgram();
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(_colorShaderProgram.aMatrixLocation, 1, GL_FALSE, mvpMatrix.m);
    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(10);
    ColorHelper::setColor(_colorShaderProgram.aColorLocation, 0xfff800);
    glDrawArrays(GL_LINE_STRIP, 0, this->polyline.getAllPoints().size());
    glDisable(GL_DEPTH_TEST);
}
