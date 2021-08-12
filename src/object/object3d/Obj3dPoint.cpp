//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include "Obj3dPoint.h"

Obj3dPoint::Obj3dPoint() : Object3d() {

}

Obj3dPoint::~Obj3dPoint() {

}

void Obj3dPoint::draw() {
    Object3d::draw();
    printf("draw Object Obj3dPoint \n");
}
