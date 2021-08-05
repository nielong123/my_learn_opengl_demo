//
// Created by 聂龙聂龙 on 2021/8/3.
//

#ifndef TESTCPP_OBJECT3D_H
#define TESTCPP_OBJECT3D_H


class Object3d {

public:
    Object3d() {};

    virtual ~Object3d() {};

    virtual void bind() { isBind = true; };

    virtual void unBind() {};

//    void draw(Mat4)

    virtual void draw() {
        std::cout << "draw Object 3d " << std::endl;
    };

private:
    bool isBind;
};

#endif //TESTCPP_OBJECT3D_H
