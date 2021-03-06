//
// Created by 聂龙聂龙 on 2021/8/2.
//

#include "VaryTools.h"

VaryTools::VaryTools() {
    viewMatrix = Mat4::IDENTITY;
    projectionMatrix = Mat4::IDENTITY;
    viewProjectionMatrix = Mat4::IDENTITY;
    scaleMatrix = Mat4::IDENTITY;
    moveMatrix = Mat4::IDENTITY;
}

void VaryTools::rotate(float angle, float x, float y, float z) {
    const Vec3 *axis = new Vec3(x, y, z);
    moveMatrix.rotate(*axis, angle);
}

void VaryTools::setCamera(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz) {
    Mat4::createLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz, &viewMatrix);
}

void VaryTools::resetVPMatrix() {
    moveMatrix = Mat4::IDENTITY;
    scaleMatrix = Mat4::IDENTITY;
    calcFinalMatrix();
}

void VaryTools::translate(float x, float y, float z) {
    moveMatrix.translate(x, y, z);
}

void VaryTools::scale(float x, float y, float z) {
    scaleMatrix.scale(x, y, z);
}

void VaryTools::scale(float scale) {
    scaleMatrix.scale(scale);
}

void VaryTools::setProjection(int width, int height) {
    Mat4::createPerspective(25, (float) width / (float) height, 1, 100, &projectionMatrix);
}

void VaryTools::calcFinalMatrix() {
    Mat4 m1;
    Mat4 m2;
    Mat4::multiply(viewMatrix, scaleMatrix, &m1);
    Mat4::multiply(m1, moveMatrix, &m2);
    Mat4::multiply(projectionMatrix, m2, &viewProjectionMatrix);
}

Mat4 VaryTools::getFinalMatrix() {
    return viewProjectionMatrix;
}

void VaryTools::print4x4Matrix(Mat4 mat4) {
    printf("%f %f %f %f \n", mat4.m[0], mat4.m[1], mat4.m[2], mat4.m[3]);
    printf("%f %f %f %f \n", mat4.m[4], mat4.m[5], mat4.m[6], mat4.m[7]);
    printf("%f %f %f %f \n", mat4.m[8], mat4.m[9], mat4.m[10], mat4.m[11]);
    printf("%f %f %f %f \n", mat4.m[12], mat4.m[13], mat4.m[14], mat4.m[15]);
    printf("/***********************************/\n");
}
