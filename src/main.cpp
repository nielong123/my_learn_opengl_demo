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
#include "object/object3d/test/Obj3dTriangle.h"
#include "cmath"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_pos_callback(GLFWwindow *window, double xPos, double yPos);

void mouse_btn_callback(GLFWwindow *window, int btn, int action, int mods);

void mouse_mid_scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

GLvoid initViewPoint();


const GLuint screen_width = 800;
const GLuint screen_height = 600;
VaryTools *_VaryTools;

//TextureShaderProgram *_TextureShaderProgram;
ColorShaderProgram *_ColorShaderProgram;

Point *_viewCenterPoint;

//鼠标位置
double mouse_x, mouse_y;
//鼠标点击位置
double mouse_hit_x = -1, mouse_hit_y = -1;
//鼠标拖动位置
double move_pos_x, move_pos_y;

//鼠标左键是否按下
bool isLeftBtnClicked = false;

//鼠标滚轮是否按下
bool isMidBtnClicked = false;

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

    Obj3dTriangle *_Obj3dTriangle = new Obj3dTriangle();
    _Obj3dTriangle->setColorShaderProgram(*_ColorShaderProgram);
    _Obj3dTriangle->setColor(0x00ffffff);
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dTriangle));

    _ColorShaderProgram->userProgram();
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

            item->draw(_VaryTools->getViewProjectionMatrix());
//            printf("glGetError() = %d \n", glGetError());
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    _ColorShaderProgram->deleteProgram();

    return 0;
}

void mouse_mid_scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    double scale = 1 + yOffset / 20;
    printf("scale = %lf \n", scale);
    _VaryTools->scale(scale);
}

void mouse_pos_callback(GLFWwindow *window, double xPos, double yPos) {
    mouse_x = xPos;
    mouse_y = yPos;
    if (isLeftBtnClicked) {
        if (mouse_hit_x != -1 && mouse_hit_y != -1) {
            move_pos_x = mouse_x - mouse_hit_x;
            move_pos_y = mouse_y - mouse_hit_y;
            int dis = ::sqrt(::pow((mouse_x - mouse_hit_x), 2) + ::pow((mouse_y - mouse_hit_y), 2));
            mouse_hit_x = -1;
            mouse_hit_y = -1;
        }
        printf("mouse_pos_callback mouse_x = %d \n", mouse_x);
        printf("mouse_pos_callback mouse_y = %d \n", mouse_y);
    }
}

void mouse_btn_callback(GLFWwindow *window, int btn, int action, int mods) {
    //鼠标左键按下
    if (action == GLFW_PRESS && btn == GLFW_MOUSE_BUTTON_LEFT) {
        isLeftBtnClicked = true;
        mouse_hit_x = mouse_x;
        mouse_hit_y = mouse_y;
        printf("mouse_hit_x  = %d \n", mouse_hit_x);
        printf("mouse_hit_y  = %d \n", mouse_hit_y);
        std::cout << "left down" << std::endl;
        return;
    } else
        //鼠标左键抬起
    if (action == GLFW_RELEASE && btn == GLFW_MOUSE_BUTTON_LEFT) {
        isLeftBtnClicked = false;
        mouse_hit_x = -1;
        mouse_hit_y = -1;
        std::cout << "left release" << std::endl;
        return;
    }
    if (action == GLFW_PRESS && btn == GLFW_MOUSE_BUTTON_MIDDLE) {
        _VaryTools->resetVPMatrix();
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
}



