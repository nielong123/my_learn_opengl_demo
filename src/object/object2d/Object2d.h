//
// Created by 聂龙聂龙 on 2021/6/29.
//

#include <iostream>

#ifndef TESTCPP_OBJECT2D_H
#define TESTCPP_OBJECT2D_H

using namespace std;

class Object2d {
public:

    Object2d() {};

    ~Object2d() {};

    virtual void bind() { isBind = true; };

    virtual void unBind() {};

    virtual void draw() {
        std::cout << "draw Object 2d " << std::endl;
    };

private:
    bool isBind;

};

#endif //TESTCPP_OBJECT2D_H
