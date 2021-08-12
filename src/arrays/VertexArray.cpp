//
// Created by 聂龙聂龙 on 2021/8/6.
//

#include "VertexArray.h"

VertexArray::VertexArray(float *vertexData) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void VertexArray::enableVertexAttributePointer(int attributeLocation, int componentCount, int dataOffset) {
    glVertexAttribPointer(attributeLocation, componentCount, GL_FLOAT, GL_FALSE,
                          componentCount * sizeof(float), (void *) dataOffset);
    glEnableVertexAttribArray(0);
}
