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
    int vertexShader = compileVertexShader(vertex_sharer);
    int fragmentShader = compileFragmentShader(fragment_sharer);
    int programId = linkProgram(vertexShader, fragmentShader);
    if (LoggerConfig::ON) {
        validateProgram(programId);
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
            printf("Warning! Could not create new shader, glGetError: %s + \n" + glGetError());
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
        printf("Result of compiling source: \n %s \n \n + %s  + \n",
               shaderCode, message);
    }
    if (compileStatus == 0) {
        glDeleteShader(shaderObjectId);
        if (LoggerConfig::ON) {
            printf("Warning! Compilation of shader failed, glGetError: %s  \n", glGetError());
        }
//        return 0;
    }
    return shaderObjectId;
}

bool ShaderHelper::validateProgram(int programId) {
    glValidateProgram(programId);
    GLint linkStatus;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &linkStatus);
    if (LoggerConfig::ON && linkStatus == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(programId, sizeof(message), 0, message);
        printf("Result of validating program: %d   \nLog: %s  \n",
               linkStatus, message);
    }
    return linkStatus != GL_FALSE;
}

int ShaderHelper::compileFragmentShader(const char *strSharer) {
    return compileShader(GL_FRAGMENT_SHADER, strSharer);
}

int ShaderHelper::compileVertexShader(const char *strSharer) {
    return compileShader(GL_VERTEX_SHADER, strSharer);
}


