//
// Created by 聂龙聂龙 on 2021/6/29.
//

#include "../../geometry/Point.h"
#include "Object2d.h"
#include <iostream>

#ifndef TESTCPP_OBJPOINT_H
#define TESTCPP_OBJPOINT_H


class ObjPoint : public Object2d {
public:
    ObjPoint() {};

    ObjPoint(Point *mPoint);

    ~ObjPoint();

private:
    Point *mPoint;

    void draw();
};


#endif //TESTCPP_OBJPOINT_H
