#ifndef MatrixState_H
#define MatrixState_H

#include "Mat4.h"

NS_CC_MATH_BEGIN

class CMatrixState {
public:
    CMatrixState();
    ~CMatrixState();

    static CMatrixState* GetMatrixState();

public:
    //不变换初始矩阵
    void SetInitStack(int nMatType);

    void setProjectOrtho(float width, float height, float zNearPlane, float zFarPlane);

    void setProjectOrthoOffCenter(float left, float right, float bottom, float top,
                                  float zNearPlane, float zFarPlane);

    /**
     * @brief 设置相机
     */
    void setLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                   float targetPositionX, float targetPositionY, float targetPositionZ,
                   float upX, float upY, float upZ);

    /**
     * @brief 平移变换
     */
    void translate(float x, float y, float z);

    /**
     * @brief 旋转
     */
    void rotate(float angle, float x, float y, float z);

    /**
     * @brief 缩放
     */
    void scale(float scale);
    void scale(float xScale, float yScale, float zScale);

    void calcFinalMatrix();
    Mat4& getFinalMatrix();
    Mat4& getProjectOrthoMatrix();

public:
    Mat4 mProjMatrix;// 投影变换
    Mat4 mVMatrix;// 摄像机位置
    Mat4 mMMatrix;// 移动旋转矩阵
    Mat4 mSMatrix;// 缩放矩阵
    Mat4 mMVPMatrix;// 最后总变换矩阵
};

NS_CC_MATH_END

#endif
