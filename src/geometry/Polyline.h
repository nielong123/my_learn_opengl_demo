//
// Created by 聂龙聂龙 on 2021/11/24.
//

#ifndef TESTCPP_POLYLINE_H
#define TESTCPP_POLYLINE_H


#include <vector>
#include "Point.h"


using namespace std;

class Polyline {
private:
    vector<const Point *> mPointVector;
public:
    void addPoint(Point *point);

    vector<const Point *> getAllPoints();

};


#endif //TESTCPP_POLYLINE_H
