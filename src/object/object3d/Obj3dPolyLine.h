//
// Created by 聂龙聂龙 on 2021/11/24.
//

#ifndef TESTCPP_OBJ3DPOLYLINE_H
#define TESTCPP_OBJ3DPOLYLINE_H


#include "../../geometry/Polyline.h"
#include "Object3d.h"

class Obj3dPolyLine : virtual public Object3d {
public:
    Obj3dPolyLine(const Polyline polyline);

    Obj3dPolyLine();

    void draw();

private:
    Polyline polyline;


};


#endif //TESTCPP_OBJ3DPOLYLINE_H
