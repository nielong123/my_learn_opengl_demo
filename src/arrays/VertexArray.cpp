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
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

}

