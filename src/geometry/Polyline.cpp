//
// Created by 聂龙聂龙 on 2021/11/24.
//

#include "Polyline.h"

void Polyline::addPoint(Point *point) {
    mPointVector.push_back(point);
}

vector<const Point *> Polyline::getAllPoints() {
    return mPointVector;
}
