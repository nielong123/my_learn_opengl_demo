//
// Created by 聂龙聂龙 on 2021/6/1.
//

#ifndef TESTCPP_TEST1_H
#define TESTCPP_TEST1_H


#include "Test2.h"

class Test1 {
public:
    Test1();

    Test1(int &i);

    virtual ~Test1();

    void add(int a, int b);

    void printI1();

private:
    std::shared_ptr<Test2> test2;
//    Test2 *test21;
    int i1;
};


#endif //TESTCPP_TEST1_H
