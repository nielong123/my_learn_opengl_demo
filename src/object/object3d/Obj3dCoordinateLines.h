//
// Created by 聂龙聂龙 on 2021/8/5.
//

#ifndef TESTCPP_OBJ3DCOORDINATELINES_H
#define TESTCPP_OBJ3DCOORDINATELINES_H


#include "Object3d.h"
#include "../../arrays/VertexArray.h"

class Obj3dCoordinateLines : virtual public Object3d {
public :
    Obj3dCoordinateLines();

    virtual ~Obj3dCoordinateLines();

    void bind();

    void unbind();

    void draw();

//    GLuint vao;
//    GLuint vbo;

private:

    float r = 3.f;
    float vertexData[18] = {0.f, r, 0.f,
                            0.f, -r, 0.f,
                            -r, 0.f, 0.f,
                            r, 0.f, 0.f,
                            0.f, 0.f, -r,
                            -0.f, 0.f, r};

//    float vertexData[9] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f, 0.5f, 0.0f  // top
//    };
};


#endif //TESTCPP_OBJ3DCOORDINATELINES_H
