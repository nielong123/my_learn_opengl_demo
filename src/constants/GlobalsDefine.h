//
// Created by 聂龙聂龙 on 2021/11/10.
//
#pragma once

#ifndef TESTCPP_GLOBALSDEFINE_H
#define TESTCPP_GLOBALSDEFINE_H

#define NDEBUG
#ifndef NDEBUG
#define GL_CHECK_ERROR(cmd) ([&]() { struct __MBGL_C_E { ~__MBGL_C_E() noexcept(false) { checkError(#cmd, __FILE__, __LINE__); } } __MBGL_C_E; return cmd; }())
#else
#define GL_CHECK_ERROR(cmd) (cmd)
#endif

#endif //TESTCPP_GLOBALSDEFINE_H
