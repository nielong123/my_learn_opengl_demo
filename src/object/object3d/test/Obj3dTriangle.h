//
// Created by 聂龙聂龙 on 2021/8/5.
//

#ifndef TESTCPP_OBJ3DTRIANGLE_H
#define TESTCPP_OBJ3DTRIANGLE_H


#include "../Object3d.h"
#include "../../../arrays/VertexArray.h"

class Obj3dTriangle : virtual public Object3d {
public :
    Obj3dTriangle();

    virtual ~Obj3dTriangle();

    void bind() override;

    void unbind() override;

    void draw() override;

private:

    float vertexData[9] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f, 0.5f, 0.0f  // top
    };
};


#endif //TESTCPP_OBJ3DTRIANGLE_H
