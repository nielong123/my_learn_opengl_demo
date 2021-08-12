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
};


#endif //TESTCPP_OBJ3DPOINT_H
