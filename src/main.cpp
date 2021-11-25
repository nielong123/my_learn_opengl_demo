#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "object/object3d/Object3d.h"
#include <vector>
#include "memory"
#include "program/ColorShaderProgram.h"
#include "helper/VaryTools.h"
#include "geometry/Point.h"
#include "object/object3d/Obj3dCoordinateLines.h"
#include "object/object3d/Obj3dTriangle.h"
#include "object/object3d/Obj3dPoint.h"
#include "Test1.h"
#include "geometry/Polyline.h"
#include "object/object3d/Obj3dPolyLine.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_pos_callback(GLFWwindow *window, double xPos, double yPos);

void mouse_btn_callback(GLFWwindow *window, int btn, int action, int mods);

void mouse_mid_scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

void renderFrame();

GLvoid initViewPoint();


const GLuint screen_width = 800;
const GLuint screen_height = 600;
VaryTools *_VaryTools;

//TextureShaderProgram *_TextureShaderProgram;
ColorShaderProgram *_ColorShaderProgram;

Point *_viewCenterPoint;

//鼠标位置
double mouse_x = -1, mouse_y = -1;


//鼠标左键是否按下
bool isLeftBtnClicked = false, isRightBtnClicked = false;

int main() {
    std::cout << "Hello, World!" << std::endl;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_btn_callback);
    glfwSetScrollCallback(window, mouse_mid_scroll_callback);

    _ColorShaderProgram = new ColorShaderProgram();

    initViewPoint();

    std::vector<Object3d *> mObjectVector;

    Obj3dCoordinateLines *_Obj3dCoordinateLines = new Obj3dCoordinateLines();
    _Obj3dCoordinateLines->setColorShaderProgram(*_ColorShaderProgram);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dCoordinateLines));

    Obj3dTriangle *_Obj3dTriangle = new Obj3dTriangle(*new Point(1.f, 1.f, 1.f),
                                                      *new Point(0.f, 1.f, 1.f),
                                                      *new Point(1.f, 0.f, 1.f),
                                                      0x123456);
//    Obj3dTriangle *_Obj3dTriangle = new Obj3dTriangle();
    _Obj3dTriangle->setColorShaderProgram(*_ColorShaderProgram);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dTriangle));

    Obj3dPoint *_Obj3dPoint = new Obj3dPoint();
    _Obj3dPoint->setColorShaderProgram(*_ColorShaderProgram);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dPoint));

    Obj3dPoint *_Obj3dPoint1 = new Obj3dPoint(2.f, 1.f, 1.f);
    _Obj3dPoint1->setColorShaderProgram(*_ColorShaderProgram);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dPoint1));

    Polyline polyline = Polyline();
    polyline.addPoint(new Point(0, 0, 0));
    polyline.addPoint(new Point(1., 1, 1));
    polyline.addPoint(new Point(-1, -1, 1));
    polyline.addPoint(new Point(-2, -2, 2));

    Obj3dPolyLine *_Obj3dPolyLine = new Obj3dPolyLine(polyline);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dPolyLine));



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Object3d *item : mObjectVector) {
            item->draw(_VaryTools->getFinalMatrix());
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

//    _ColorShaderProgram->deleteProgram();

    return 0;
}

void mouse_mid_scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    double scale = 1 + yOffset / 20;
    printf("scale = %lf \n", scale);
    _VaryTools->scale(scale);
    _VaryTools->calcFinalMatrix();
    renderFrame();
}

void mouse_pos_callback(GLFWwindow *window, double xPos, double yPos) {
    if (isLeftBtnClicked) {
        if (mouse_x != -1 && mouse_y != -1) {
            float move_pos_x = xPos - mouse_x;
            float move_pos_y = yPos - mouse_y;
//            if (move_pos_x > 1 || move_pos_y > 1) {
            _VaryTools->rotate(0.1, move_pos_y, move_pos_x, 0);
            _VaryTools->calcFinalMatrix();
            renderFrame();
//            }
//            printf("mouse_x = %f \n", move_pos_x);
//            printf("mouse_y = %f \n", move_pos_y);
        }
        mouse_x = xPos;
        mouse_y = yPos;
        return;
    }
    if (isRightBtnClicked) {
        if (mouse_x != -1 && mouse_y != -1) {
            float move_pos_x = (xPos - mouse_x) / 100;
            float move_pos_y = -(yPos - mouse_y) / 100;
            _VaryTools->translate(move_pos_x, move_pos_y, 0);
            _VaryTools->calcFinalMatrix();
//            printf("mouse_x = %f \n", move_pos_x);
//            printf("mouse_y = %f \n", move_pos_y);
            renderFrame();
        }
        mouse_x = xPos;
        mouse_y = yPos;
    }
}

void mouse_btn_callback(GLFWwindow *window, int btn, int action, int mods) {
    //鼠标左键按下
    if (action == GLFW_PRESS && btn == GLFW_MOUSE_BUTTON_LEFT) {
        isLeftBtnClicked = true;
        return;
    }
    //鼠标左键抬起
    if (action == GLFW_RELEASE && btn == GLFW_MOUSE_BUTTON_LEFT) {
        isLeftBtnClicked = false;
        mouse_x = -1;
        mouse_y = -1;
        return;
    }
    //鼠标右键按下
    if (action == GLFW_PRESS && btn == GLFW_MOUSE_BUTTON_RIGHT) {
        isRightBtnClicked = true;
        return;
    }
    //鼠标右键抬起
    if (action == GLFW_RELEASE && btn == GLFW_MOUSE_BUTTON_RIGHT) {
        isRightBtnClicked = false;
        mouse_x = -1;
        mouse_y = -1;
        return;
    }
    //鼠标滚轮按下
    if (action == GLFW_PRESS && btn == GLFW_MOUSE_BUTTON_MIDDLE) {
        _VaryTools->resetVPMatrix();
        renderFrame();
        return;
    }
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(_viewCenterPoint->x, _viewCenterPoint->y, width, height);
}

GLvoid initViewPoint() {
    _viewCenterPoint = new Point(0.5f, 0.5f, 0.5f);
    _VaryTools = new VaryTools();
    _VaryTools->setCamera(4.f, 4.f, 4.f,
                          _viewCenterPoint->x, _viewCenterPoint->y, _viewCenterPoint->z,
                          0.f, 1.f, 0.f);
    _VaryTools->setProjection(screen_width, screen_height);
    _VaryTools->calcFinalMatrix();
}

void renderFrame() {
//    isRender = true;
}



