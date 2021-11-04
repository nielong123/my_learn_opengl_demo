//
// Created by 聂龙聂龙 on 2021/8/2.
//

#ifndef TESTCPP_VARYTOOLS_H
#define TESTCPP_VARYTOOLS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/matrixUtil/Mat4.h"

using namespace cocos2d;


class VaryTools {

public:
    VaryTools();

    ~VaryTools() {};

    //旋转
    void rotate(float angle, float x, float y, float z);

    //设置相机位置
    void setCamera(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz);

    //平移变换
    void translate(float x, float y, float z);

    //缩放变换
    void scale(float x, float y, float z);

    //缩放变换
    void scale(float scale);

    //初始化投影
    void setProjection(int width, int height);

    //重制投影视角矩阵
    void resetVPMatrix();

    Mat4 getViewProjectionMatrix();

public:

    static void print4x4Matrix(Mat4 mat4);

private:
    Mat4 viewMatrix;
    Mat4 orgViewMatrix;
    Mat4 projectionMatrix;
    Mat4 orgProjectMatrix;
    Mat4 viewProjectionMatrix;
};


#endif //TESTCPP_VARYTOOLS_H
