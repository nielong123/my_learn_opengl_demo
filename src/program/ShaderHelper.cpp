//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include <iostream>
#include "ShaderHelper.h"
#include "glad/glad.h"
#include "../helper/LoggerConfig.h"
#include "GLFW/glfw3.h"

using namespace std;


int ShaderHelper::buildProgram(const char *vertex_sharer, const char *fragment_sharer) {
    int vertexShader = compileVertexShader(STR_VERTEX_SHADER);
    int fragmentShader = compileFragmentShader(STR_VERTEX_SHADER);
    int programId = linkProgram(vertexShader, fragmentShader);
    if (LoggerConfig::ON) {
        validateProgram();
    }
    return programId;
}

int ShaderHelper::linkProgram(int vertexShader, int fragmentShader) {

    return 0;
}


int ShaderHelper::compileShader(int type, const char *shaderCode) {
    const int shaderObjectId = glCreateShader(type);
    if (shaderObjectId == 0) {
        if (LoggerConfig::ON) {
            printf("Warning! Could not create new shader, glGetError: " + glGetError());
        }
        return 0;
    }
    glShaderSource(shaderObjectId, 1, &shaderCode, 0);
    glCompileShader(shaderObjectId);
    GLint compileStatus;
    glGetShaderiv(shaderObjectId, GL_COMPILE_STATUS, &compileStatus);
    if (LoggerConfig::ON) {
        GLchar message[256];
        glGetShaderInfoLog(shaderObjectId, sizeof(message), 0, message);
        printf("Result of compiling source: \n %s \n \n + %s",
               shaderCode, message);
    }
    if (compileStatus == 0) {
        glDeleteShader(shaderObjectId);
        if (LoggerConfig::ON) {
            printf("Warning! Compilation of shader failed, glGetError: %s", glGetError());
        }
        return 0;
    }
    return shaderObjectId;
}


int ShaderHelper::compileFragmentShader(const char *vertex_sharer) {
    return compileShader(GL_FRAGMENT_SHADER, STR_VERTEX_SHADER);
}

int ShaderHelper::compileVertexShader(const char *vertex_sharer) {
    return compileShader(GL_VERTEX_SHADER, vertex_sharer);
}

void ShaderHelper::validateProgram() {

}


