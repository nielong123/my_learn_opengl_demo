//
// Created by 聂龙聂龙 on 2021/6/29.
//

#include "ObjPoint.h"

ObjPoint::ObjPoint(Point *mPoint) {
    this->mPoint = mPoint;
}

void ObjPoint::draw() {
    std::cout << "draw ObjPoint " << std::endl;
}

ObjPoint::~ObjPoint() {

}
