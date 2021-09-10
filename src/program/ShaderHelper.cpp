//
// Created by 聂龙聂龙 on 2021/7/26.
//

#include <iostream>
#include "ShaderHelper.h"
#include "glad/glad.h"
#include "../helper/LoggerConfig.h"

using namespace std;


int ShaderHelper::buildProgram(const char *vertex_sharer, const char *fragment_sharer) {
    int vertexShader = compileVertexShader(vertex_sharer);
    printf("\n\n\n\n");
    int fragmentShader = compileFragmentShader(fragment_sharer);
    int programId = linkProgram(vertexShader, fragmentShader);
    if (LoggerConfig::ON) {
        validateProgram(programId);
    }
    return programId;
}

int ShaderHelper::linkProgram(int vertexShaderId, int fragmentShaderId) {
    const int programObjId = glCreateProgram();
    if (programObjId == 0) {
        if (LoggerConfig::ON) {
            printf(" Warning! Could not create new program, glGetError:  = %d \n", glGetError());
        }
        return 0;
    }
    glAttachShader(programObjId, vertexShaderId);
    glAttachShader(programObjId, fragmentShaderId);
    glLinkProgram(programObjId);
    GLint linkStatus;
    glGetProgramiv(programObjId, GL_LINK_STATUS, &linkStatus);

    if (LoggerConfig::ON && !linkStatus) {
        GLchar message[256];
        glGetProgramInfoLog(programObjId, sizeof(message), NULL, message);
        printf("Result of validating program: %d   \nLog: %s  \n",
               linkStatus, message);
    }
    if (!linkStatus) {
        glDeleteProgram(programObjId);
        if (LoggerConfig::ON) {
            printf(" Warning! Linking of program failed, glGetError: %d \n", glGetError());
        }
        return 0;
    }
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programObjId;
}

/***
 * 用glsl链接着色器程序
 * @param type
 * @param shaderCode
 * @return
 */
int ShaderHelper::compileShader(int type, const char *shaderCode) {
    const int shaderObjectId = glCreateShader(type);
    if (shaderObjectId == 0) {
        if (LoggerConfig::ON) {
            printf("Warning! Could not create new shader, glGetError: %s  \n" + glGetError());
        }
        return 0;
    }
    glShaderSource(shaderObjectId, 1, &shaderCode, NULL);
    glCompileShader(shaderObjectId);
    GLint compileStatus;
    glGetShaderiv(shaderObjectId, GL_COMPILE_STATUS, &compileStatus);
    if (LoggerConfig::ON && !compileStatus) {
        GLchar message[256];
        glGetShaderInfoLog(shaderObjectId, sizeof(message), NULL, message);
        printf("Result of compiling source: \n %s \n \n %s  \n",
               shaderCode, message);
    }
    if (compileStatus == 0) {
        glDeleteShader(shaderObjectId);
        if (LoggerConfig::ON) {
            printf("Warning! Compilation of shader failed, glGetError: %d  \n", glGetError());
        }
        return 0;
    }
    return shaderObjectId;
}

/***
 * 验证programId 是否有效
 * @param programId
 * @return
 */
bool ShaderHelper::validateProgram(int programId) {
    glValidateProgram(programId);
    GLint linkStatus;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &linkStatus);
//    if (LoggerConfig::ON && !linkStatus) {
//        GLchar message[256];
//        glGetProgramInfoLog(programId, sizeof(message), NULL, message);
//        printf("11Result of validating program: %d   \nLog: %s  \n",
//               linkStatus, message);
//    }
    return linkStatus != GL_FALSE;
}

int ShaderHelper::compileFragmentShader(const char *strSharer) {
    return compileShader(GL_FRAGMENT_SHADER, strSharer);
}

int ShaderHelper::compileVertexShader(const char *strSharer) {
    return compileShader(GL_VERTEX_SHADER, strSharer);
}


