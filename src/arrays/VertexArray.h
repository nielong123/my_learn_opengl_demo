//
// Created by 聂龙聂龙 on 2021/8/6.
//

#ifndef TESTCPP_VERTEXARRAY_H
#define TESTCPP_VERTEXARRAY_H


#include <glad/glad.h>

class VertexArray {
public:
    VertexArray(float vertexData[]);

    void enableVertexAttributePointer(int attributeLocation,
                                      int componentCount, int dataOffset);


private:
    GLuint vao;
};


#endif //TESTCPP_VERTEXARRAY_H
