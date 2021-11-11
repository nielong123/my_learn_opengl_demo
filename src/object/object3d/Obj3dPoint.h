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

    Obj3dPoint(float x, float y, float z);

    Obj3dPoint(float x, float y, float z, int color);

    ~Obj3dPoint();

    void draw();

private:

    int rgbColor = 0xffffff;

    float vertexData[3] = {
            1.5f, 1.f, 1.f,
    };

    void bind() override;

    void unbind() override;
};


#endif //TESTCPP_OBJ3DPOINT_H
