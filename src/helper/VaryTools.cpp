//
// Created by 聂龙聂龙 on 2021/8/2.
//

#include "VaryTools.h"

VaryTools::VaryTools() {
    viewMatrix = Mat4::IDENTITY;
    projectionMatrix = Mat4::IDENTITY;
    viewProjectionMatrix = Mat4::IDENTITY;
}

void VaryTools::rotate(float angle, float x, float y, float z) {
    const Vec3 *axis = new Vec3(x, y, z);
    viewProjectionMatrix.rotate(*axis, angle);
}

void VaryTools::setCamera(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz) {
    Mat4::createLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz, &viewMatrix);
}

void VaryTools::resetVPMatrix() {
    viewProjectionMatrix = Mat4::IDENTITY;
}

void VaryTools::translate(float x, float y, float z) {
    viewProjectionMatrix.translate(x, y, z);
}

void VaryTools::scale(float x, float y, float z) {
    viewProjectionMatrix.scale(x, y, z);
}

void VaryTools::setProjection(int width, int height) {
    Mat4::createPerspective(100, 35, width, height, &projectionMatrix);
}

void VaryTools::getViewProjectionMatrix(Mat4 &matrix) {
    Mat4 ans = Mat4::IDENTITY;
    Mat4::multiply(ans, viewMatrix, &ans);
}
