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
//    glUniformMatrix4fv(1, 1, false, mvpMatrix.m);

    glUniform4f(_colorShaderProgram.aColorLocation, 0.3f, 0.3f, 0.3f, 0.3f);

    glVertexAttribPointer(_colorShaderProgram.aPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
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



