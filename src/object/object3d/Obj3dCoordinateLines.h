//
// Created by 聂龙聂龙 on 2021/8/5.
//

#ifndef TESTCPP_OBJ3DCOORDINATELINES_H
#define TESTCPP_OBJ3DCOORDINATELINES_H


#include "Object3d.h"

class Obj3dCoordinateLines : virtual public Object3d {
public :
    void unBind();

    void draw();

private:
    float r = 3.f;
    float vertexData[18] = {0.f, r, 0.f,
                            0.f, -r, 0.f,
                            -r, 0.f, 0.f,
                            r, 0.f, 0.f,
                            0.f, 0.f, -r,
                            -0.f, 0.f, r};
};


#endif //TESTCPP_OBJ3DCOORDINATELINES_H
