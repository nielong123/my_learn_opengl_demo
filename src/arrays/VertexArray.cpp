//
// Created by 聂龙聂龙 on 2021/8/6.
//

#include "VertexArray.h"

VertexArray::VertexArray(float data[], int vertexLength, GLuint &vao, GLuint &vbo) {
    float vertexData[vertexLength];
    for (int i = 0; i < vertexLength; ++i) {
        vertexData[i] = data[i];
    }
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
//    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

