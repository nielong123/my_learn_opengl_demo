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
        src/geometry/Point.cpp src/geometry/Point.cpp
        src/geometry/Point.cpp src/geometry/Point.h src/object/object2d/ObjPoint.cpp src/object/object2d/ObjPoint.h src/object/object3d/Point.cpp src/object/object3d/Point.h src/program/ShaderHelper.cpp src/program/ShaderHelper.h src/helper/LoggerConfig.h)

target_link_libraries(testCpp
        glfw
        )