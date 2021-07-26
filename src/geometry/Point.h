//
// Created by 聂龙聂龙 on 2021/6/29.
//

#ifndef TESTCPP_POINT_H
#define TESTCPP_POINT_H


class Point {
public:
    Point();

    Point(float x, float y, float z);

    ~Point();

public:
    float x, y, z;
    float color;

};


#endif //TESTCPP_POINT_H
