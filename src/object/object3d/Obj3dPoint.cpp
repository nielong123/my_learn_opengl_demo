//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include "Obj3dPoint.h"

Obj3dPoint::Obj3dPoint() : Object3d() {
    _VertexArray = new VertexArray(vertexData, sizeof(vertexData) / sizeof(*vertexData), vao, vbo);
}

Obj3dPoint::~Obj3dPoint() {

}

void Obj3dPoint::draw() {
    Object3d::draw();
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, 3);
}

void Obj3dPoint::bind() {
    glUniformMatrix4fv(1, 1, false, mvpMatrix.m);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}
