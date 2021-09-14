//
// Created by 聂龙聂龙 on 2021/7/26.
//

#ifndef TESTCPP_OBJ3DPOINT_H
#define TESTCPP_OBJ3DPOINT_H

#include <iostream>
#include "Object3d.h"

using namespace std;

class Obj3dPoint : virtual public Object3d {
public:
    Obj3dPoint();

    ~Obj3dPoint();

    void draw();

private:
    float vertexData[9] = {
            -0.6f, -0.3f, 0.1f, // left
            0.8f, -0.56f, 0.0f, // right
            0.24f, 0.1f, 0.9f  // top
    };

    void bind();
};


#endif //TESTCPP_OBJ3DPOINT_H
