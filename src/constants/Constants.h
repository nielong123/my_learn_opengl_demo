//
// Created by 聂龙聂龙 on 2021/7/30.
//

#ifndef TESTCPP_CONSTANTS_H
#define TESTCPP_CONSTANTS_H

class Constants {
public:
    inline static const char *A_COLOR = "aColor";
    inline static const char *A_POSITION = "aPos";          //aPos 和glsl里的layout (location = 0) 是等价的
    inline static const char *A_MATRIX = "aMatrix";


    inline static const char *U_MATRIX = "u_Matrix";
    inline static const char *A_POINTSIZE = "m_pointSize";
    inline static const char *U_TEXTURE_UNIT = "u_TextureUnit";
    inline static const char *A_TEXTURE_COORDINATES = "a_TextureCoordinates";
};

#endif //TESTCPP_CONSTANTS_H
