#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "object/object3d/Object3d.h"
#include <vector>
#include "memory"
#include "program/ColorShaderProgram.h"
#include "program/TextureShaderProgram.h"
#include "object/object3d/Obj3dPoint.h"
#include "helper/VaryTools.h"
#include "geometry/Point.h"
#include "object/object3d/Obj3dCoordinateLines.h"
#include "object/TestFunction.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

GLvoid initViewPoint();


const GLuint screen_width = 800;
const GLuint screen_height = 600;
VaryTools *_VaryTools;

//TextureShaderProgram *_TextureShaderProgram;
ColorShaderProgram *_ColorShaderProgram;

Point *_viewCenterPoint;


float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f  // top
};

void testDraw(GLuint VAO) {
    _ColorShaderProgram->userProgram();
    glBindVertexArray(
            VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

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

//    initViewPoint();
    GLuint vao, vbo;
    _ColorShaderProgram = new ColorShaderProgram();
//    TestFunction::testInit111(vertices, sizeof(vertices) / sizeof(*vertices), vao, vbo);
//    TestFunction::testInit(vao, vbo);

//    testInit();

    std::vector<Object3d *> mObjectVector;
//    Obj3dPoint *_Obj3dPoint = new Obj3dPoint();
//    _Obj3dPoint->setColorShaderProgram(*_ColorShaderProgram);
    Obj3dCoordinateLines *_Obj3dCoordinateLines = new Obj3dCoordinateLines();
//    _Obj3dCoordinateLines->setColorShaderProgram(*_ColorShaderProgram);
//    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dPoint));
    mObjectVector.push_back(static_cast<Object3d *>(_Obj3dCoordinateLines));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (Object3d *item : mObjectVector) {
////            Mat4 mat = _VaryTools->getViewProjectionMatrix();
////            item->draw(mat);
//        _ColorShaderProgram->userProgram();
            item->draw();
//        printf("glGetError() = %d \n", glGetError());
//        testDraw(vao);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();


    return 0;
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
    glViewport(0, 0, width, height);
}

GLvoid initViewPoint() {
    _viewCenterPoint = new Point(0.5f, 0.5f, 0.5f);
    _VaryTools = new VaryTools();
    _VaryTools->setCamera(4.f, 4.f, 4.f,
                          _viewCenterPoint->x, _viewCenterPoint->y, _viewCenterPoint->z,
                          0.f, 1.f, 0.f);
    _VaryTools->setProjection(screen_width, screen_height);
}
