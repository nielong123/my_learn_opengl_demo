#include "MatrixState.h"

NS_CC_MATH_BEGIN

static CMatrixState* g_MatrixState = NULL;

CMatrixState* CMatrixState::GetMatrixState()
{
    if (g_MatrixState == NULL) {
        g_MatrixState = new CMatrixState();
    }

    return (g_MatrixState);
}

CMatrixState::CMatrixState()
{
    SetInitStack(1);
    SetInitStack(2);
}

CMatrixState::~CMatrixState()
{
    if (g_MatrixState != NULL) {
        delete g_MatrixState;
        g_MatrixState = NULL;
    }
}

void CMatrixState::SetInitStack(int nMatType)
{
    if (nMatType == 1) {
        mMMatrix = Mat4::IDENTITY;
    } else if (nMatType == 2) {
        mSMatrix = Mat4::IDENTITY;
    }
}

void CMatrixState::setProjectOrtho(float width, float height, float zNearPlane, float zFarPlane)
{
    Mat4::createOrthographic(width, height, zNearPlane, zFarPlane, &mProjMatrix);
}

void CMatrixState::setProjectOrthoOffCenter(float left, float right, float bottom, float top,
    float zNearPlane, float zFarPlane)
{
    Mat4::createOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane,
                                      &mProjMatrix);

    // 需要判断是否设置了mvp
    mMVPMatrix.setIdentity();
    mVMatrix.setIdentity();
    mMMatrix.setIdentity();
}

void CMatrixState::setLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                             float targetPositionX, float targetPositionY, float targetPositionZ,
                             float upX, float upY, float upZ)
{
    Mat4::createLookAt(eyePositionX, eyePositionY, eyePositionZ, targetPositionX,
                       targetPositionY, targetPositionZ, upX, upY, upZ, &mVMatrix);
}

void CMatrixState::translate(float x, float y, float z)
{
    mMMatrix.translate(x, y, z);
}

void CMatrixState::rotate(float angle, float x, float y, float z)
{
    // 对于平面内的地图，旋转为直接绕Z轴旋转
    // mMMatrix.rotate(Vec3(x, y, z), angle);
    // mMMatrix.rotate(Vec3(0, y, z), angle);
    mMMatrix.rotateZ(angle);
    // mMMatrix.rotateX(angle);
}

void CMatrixState::scale(float scale)
{
    mSMatrix.scale(scale, scale, 1);
}

void CMatrixState::scale(float xScale, float yScale, float zScale)
{
    mSMatrix.scale(xScale, yScale, zScale);
}

Mat4& CMatrixState::getFinalMatrix()
{
    return (mMVPMatrix);
    // return (mProjMatrix);
}

void CMatrixState::calcFinalMatrix()
{
    Mat4 m1, m2;
    Mat4::multiply(mVMatrix, mSMatrix, &m1);
    Mat4::multiply(m1, mMMatrix, &m2);
    Mat4::multiply(mProjMatrix, m2, &mMVPMatrix);
}

#if 0
Mat4& CMatrixState::getFinalMatrix()
{
    // Mat4 m1;
    // Mat4::multiply(mVMatrix,mMMatrix,&m1);
    // Mat4::multiply(mProjMatrix,m1,&mMVPMatrix);
    Mat4 m1, m2;
    Mat4::multiply(mVMatrix, mSMatrix, &m1);
    Mat4::multiply(m1, mMMatrix, &m2);
    Mat4::multiply(mProjMatrix, m2, &mMVPMatrix);
    return (mMVPMatrix);
}
#endif

Mat4& CMatrixState::getProjectOrthoMatrix()
{
    return (mProjMatrix);
}

NS_CC_MATH_END

