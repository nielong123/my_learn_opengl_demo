cmake_minimum_required(VERSION 3.19)
project(testCpp)

set(CMAKE_CXX_STANDARD 11)

#头文件
set(GLAD_INCLUDE /usr/local/Cellar/glfw/3.3.2/include)
set(GLEW_INCLUDE /usr/local/Cellar/glew/2.1.0/include/GL)

find_package(glfw3 REQUIRED)

include_directories(${GLAD_INCLUDE} ${GLEW_INCLUDE})

add_executable(testCpp
        src/main.cpp
        src/Test1.cpp
        src/Test1.h
        src/Test2.cpp
        src/Test2.h
        src/glad.c
        src/object/object2d/Object2d.h
        src/geometry/Point.cpp
        src/geometry/Point.h
        src/object/object2d/ObjPoint.cpp
        src/object/object2d/ObjPoint.h
        src/object/object3d/Obj3dPoint.cpp
        src/object/object3d/Obj3dPoint.h
        src/program/ShaderHelper.cpp
        src/program/ShaderHelper.h
        src/helper/LoggerConfig.h
        src/program/ShaderProgram.cpp
        src/program/ShaderProgram.h
        src/program/ColorShaderProgram.cpp
        src/program/ColorShaderProgram.h
        src/constants/Constants.h
        src/constants/Constants.cpp
        src/program/TextureShaderProgram.cpp
        src/program/TextureShaderProgram.h
        src/helper/VaryTools.cpp
        src/helper/VaryTools.h
        src/object/object3d/Object3d.h
        src/include/matrixUtil/CCData.cpp
        src/include/matrixUtil/CCData.h
        src/include/matrixUtil/Vec4.h
        src/include/matrixUtil/Vec4.cpp
        src/include/matrixUtil/Vec4.inl
        src/include/matrixUtil/Vec3.h
        src/include/matrixUtil/Vec3.cpp
        src/include/matrixUtil/Vec3.inl
        src/include/matrixUtil/Mat4.cpp
        src/include/matrixUtil/Mat4.h
        src/include/matrixUtil/Mat4.inl

        src/object/object3d/Obj3dCoordinateLines.cpp
        src/object/object3d/Obj3dCoordinateLines.h
        src/arrays/VertexArray.cpp
        src/arrays/VertexArray.h src/object/TestFunction.cpp src/object/TestFunction.h)

target_link_libraries(testCpp
        glfw
        )