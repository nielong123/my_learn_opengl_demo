//
// Created by 聂龙聂龙 on 2021/8/5.
//

#ifndef TESTCPP_OBJ3DTRIANGLE_H
#define TESTCPP_OBJ3DTRIANGLE_H

#include <glad/glad.h>
#include "Object3d.h"
#include "../../arrays/VertexArray.h"
#include "../../geometry/Point.h"


class Obj3dTriangle : virtual public Object3d {
public :
    Obj3dTriangle();

    Obj3dTriangle(Point &point1, Point &point2, Point &point3, int hexColor);

    virtual ~Obj3dTriangle();

    void bind() override;

    void unbind() override;

    void draw() override;

    void setFillColor(int hexARGBColor);

private:

    float vertexData[9] = {
            -1.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            1.0f, 0.5f, 1.0f  // top
    };

    int fillColor;
};


#endif //TESTCPP_OBJ3DTRIANGLE_H
