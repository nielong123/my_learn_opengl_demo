//
// Created by 聂龙聂龙 on 2021/6/1.
//
#include <iostream>
#include "Test1.h"

using namespace std;


void Test1::add(int a, int b) {
    test2->printHello();
//    test21->printHello();
    int c = a + b;
    std::cout << std::to_string(c) << std::endl;
}

Test1::Test1() {

}

Test1::~Test1() {

}



