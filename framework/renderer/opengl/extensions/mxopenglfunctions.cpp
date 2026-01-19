/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

/****************************************************************************
** Copyright (C) 2020 Hugo Silva. All rights reserved.
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Hugo Silva <hugo@mewatools.com>, April 2020
****************************************************************************/

#include "mxdebug.h"
#include "mxopenglfunctions.h"

#ifdef __EMSCRIPTEN__
#include "EGL/egl.h"
#endif

// QxGLExtensions *QxGLExtensions::sExtensionsInstance = NULL;

#if defined(QX_PLATFORM_OSX)
#import <mach-o/dyld.h>
#import <stdlib.h>
#import <string.h>
void *qt_gl_getProcAddress(const char *name)
{
    NSSymbol symbol;
    char *symbolName;
    symbolName = (char *)malloc(strlen(name) + 2); // 1
    strcpy(symbolName + 1, name);                  // 2
    symbolName[0] = '_';                           // 3
    symbol = NULL;
    if (NSIsSymbolNameDefined(symbolName)) // 4
        symbol = NSLookupAndBindSymbol(symbolName);
    free(symbolName);                                 // 5
    return symbol ? NSAddressOfSymbol(symbol) : NULL; // 6
}
#else

void *MxOpenGLFunctions::qx_getProcAddress(const char *name)
{
    void *addr;
#if defined(__linux__)
    addr = (void *)glXGetProcAddressARB((const GLubyte *)name);
#elif _WIN32
    addr = (void *)wglGetProcAddress(name);
    if (!addr)
    {
        addr = (void *)GetProcAddress(gl_module, name);
    }
#elif Q_OS_ANDROID
    addr = (void *)eglGetProcAddress(name);
#elif __EMSCRIPTEN__
    addr = (void *)eglGetProcAddress(name);
#endif

    return addr;
}

void *MxOpenGLFunctions::qx_gl_getProcAddress_search(const char *name1, const char *name2, const char *name3)
{
    void *addr;
    addr = qx_getProcAddress(name1);
    if (addr)
        return addr;

    addr = qx_getProcAddress(name2);
    if (addr)
        return addr;

    addr = qx_getProcAddress(name3);
    if (addr)
        return addr;

    return 0;
}

// Search for an extension function starting with the most likely
// function suffix first, and then trying the other variations.
#define qt_gl_getProcAddress(name) \
    qx_gl_getProcAddress_search(name, name "ARB", name "EXT")

#endif

MxOpenGLFunctions::MxOpenGLFunctions()
{
}

bool MxOpenGLFunctions::init()
{
    // Q_ASSERT( NULL == sExtensionsInstance );
    // sExtensionsInstance = new QxGLExtensions;

#ifdef _WIN32
    gl_module = LoadLibrary(TEXT("opengl32.dll"));
#endif

    glBlendFunc = (_glBlendFunc)qt_gl_getProcAddress("glBlendFunc");
    // Q_ASSERT( NULL != qt_glBlendFunc );
    glClear = (_glClear)qt_gl_getProcAddress("glClear");
    glClearColor = (_glClearColor)qt_gl_getProcAddress("glClearColor");
    glClearStencil = (_glClearStencil)qt_gl_getProcAddress("glClearStencil");
    glEnable = (_glEnable)qt_gl_getProcAddress("glEnable");
    glViewport = (_glViewport)qt_gl_getProcAddress("glViewport");

    glColorMask = (_glColorMask)qt_gl_getProcAddress("glColorMask");
    glStencilOp = (_glStencilOp)qt_gl_getProcAddress("glStencilOp");
    glStencilMask = (_glStencilMask)qt_gl_getProcAddress("glStencilMask");
    glStencilFunc = (_glStencilFunc)qt_gl_getProcAddress("glStencilFunc");

    glScissor = (_glScissor)qt_gl_getProcAddress("glScissor");
    glDisable = (_glDisable)qt_gl_getProcAddress("glDisable");
    glBlendEquation = (_glBlendEquation)qt_gl_getProcAddress("glBlendEquation");

    glLineWidth = (_glLineWidth)qt_gl_getProcAddress("glLineWidth");

    glActiveTexture = (_glActiveTexture)qt_gl_getProcAddress("glActiveTexture");

    glGenTextures = (_glGenTextures)qt_gl_getProcAddress("glGenTextures");
    glTexImage2D = (_glTexImage2D)qt_gl_getProcAddress("glTexImage2D");
    glTexSubImage2D = (_glTexSubImage2D)qt_gl_getProcAddress("glTexSubImage2D");
    glTexImage3D = (_glTexImage3D)qt_gl_getProcAddress("glTexImage3D");
    glTexSubImage3D = (_glTexSubImage3D)qt_gl_getProcAddress("glTexSubImage3D");
    glPixelStorei = (_glPixelStorei)qt_gl_getProcAddress("glPixelStorei");
    glReadPixels = (_glReadPixels)qt_gl_getProcAddress("glReadPixels");
    glDeleteTextures = (_glDeleteTextures)qt_gl_getProcAddress("glDeleteTextures");
    glGetIntegerv = (_glGetIntegerv)qt_gl_getProcAddress("glGetIntegerv");

    glTexParameterf = (_glTexParameterf)qt_gl_getProcAddress("glTexParameterf");
    glTexParameterfv = (_glTexParameterfv)qt_gl_getProcAddress("glTexParameterfv");
    glTexParameteri = (_glTexParameteri)qt_gl_getProcAddress("glTexParameteri");
    glTexParameteriv = (_glTexParameteriv)qt_gl_getProcAddress("glTexParameteriv");

    glBindRenderbuffer = (_glBindRenderbuffer)qt_gl_getProcAddress("glBindRenderbuffer");
    glDeleteRenderbuffers = (_glDeleteRenderbuffers)qt_gl_getProcAddress("glDeleteRenderbuffers");
    glGenRenderbuffers = (_glGenRenderbuffers)qt_gl_getProcAddress("glGenRenderbuffers");
    glRenderbufferStorage = (_glRenderbufferStorage)qt_gl_getProcAddress("glRenderbufferStorage");
    glGetRenderbufferParameteriv = (_glGetRenderbufferParameteriv)qt_gl_getProcAddress("glGetRenderbufferParameteriv");
    glIsFramebuffer = (_glIsFramebuffer)qt_gl_getProcAddress("glIsFramebuffer");
    glBindFramebuffer = (_glBindFramebuffer)qt_gl_getProcAddress("glBindFramebuffer");
    glDeleteFramebuffers = (_glDeleteFramebuffers)qt_gl_getProcAddress("glDeleteFramebuffers");
    glGenFramebuffers = (_glGenFramebuffers)qt_gl_getProcAddress("glGenFramebuffers");
    glCheckFramebufferStatus = (_glCheckFramebufferStatus)qt_gl_getProcAddress("glCheckFramebufferStatus");
    glFramebufferTexture2D = (_glFramebufferTexture2D)qt_gl_getProcAddress("glFramebufferTexture2D");
    glFramebufferRenderbuffer = (_glFramebufferRenderbuffer)qt_gl_getProcAddress("glFramebufferRenderbuffer");
    /*qx_glGetFramebufferAttachmentParameteriv =
        (_glGetFramebufferAttachmentParameteriv) qt_gl_getProcAddress(ctx, "glGetFramebufferAttachmentParameteriv");
        */

    glUseProgram = (_glUseProgram)qt_gl_getProcAddress("glUseProgram");
    glGetAttribLocation = (_glGetAttribLocation)qt_gl_getProcAddress("glGetAttribLocation");
    glGetUniformLocation = (_glGetUniformLocation)qt_gl_getProcAddress("glGetUniformLocation");
    glDeleteProgram = (_glDeleteProgram)qt_gl_getProcAddress("glDeleteProgram");
    glDeleteShader = (_glDeleteShader)qt_gl_getProcAddress("glDeleteShader");
    glShaderSource = (_glShaderSource)qt_gl_getProcAddress("glShaderSource");
    glGetShaderiv = (_glGetShaderiv)qt_gl_getProcAddress("glGetShaderiv");
    glCreateProgram = (_glCreateProgram)qt_gl_getProcAddress("glCreateProgram");
    glCreateShader = (_glCreateShader)qt_gl_getProcAddress("glCreateShader");
    glAttachShader = (_glAttachShader)qt_gl_getProcAddress("glAttachShader");
    glDetachShader = (_glDetachShader)qt_gl_getProcAddress("glDetachShader");

    glCompileShader = (_glCompileShader)qt_gl_getProcAddress("glCompileShader");
    glLinkProgram = (_glLinkProgram)qt_gl_getProcAddress("glLinkProgram");
    glGetProgramiv = (_glGetProgramiv)qt_gl_getProcAddress("glGetProgramiv");

    glGetShaderInfoLog = (_glGetShaderInfoLog)qt_gl_getProcAddress("glGetShaderInfoLog");
    glGetProgramInfoLog = (_glGetProgramInfoLog)qt_gl_getProcAddress("glGetProgramInfoLog");

    glGetUniformLocation = (_glGetUniformLocation)qt_gl_getProcAddress("glGetUniformLocation");
    glUniform4fv = (_glUniform4fv)qt_gl_getProcAddress("glUniform4fv");
    glUniform3fv = (_glUniform3fv)qt_gl_getProcAddress("glUniform3fv");
    glUniform2fv = (_glUniform2fv)qt_gl_getProcAddress("glUniform2fv");
    glUniform1fv = (_glUniform1fv)qt_gl_getProcAddress("glUniform1fv");

    glUniform1f = (_glUniform1f)qt_gl_getProcAddress("glUniform1f");
    glUniform2f = (_glUniform2f)qt_gl_getProcAddress("glUniform2f");
    glUniform3f = (_glUniform3f)qt_gl_getProcAddress("glUniform3f");
    glUniform4f = (_glUniform4f)qt_gl_getProcAddress("glUniform4f");
    glUniform1i = (_glUniform1i)qt_gl_getProcAddress("glUniform1i");
    glUniform1iv = (_glUniform1iv)qt_gl_getProcAddress("glUniform1iv");
    glUniformMatrix2fv = (_glUniformMatrix2fv)qt_gl_getProcAddress("glUniformMatrix2fv");
    glUniformMatrix3fv = (_glUniformMatrix3fv)qt_gl_getProcAddress("glUniformMatrix3fv");
    glUniformMatrix4fv = (_glUniformMatrix4fv)qt_gl_getProcAddress("glUniformMatrix4fv");
    glUniformMatrix2x3fv = (_glUniformMatrix2x3fv)qt_gl_getProcAddress("glUniformMatrix2x3fv");
    glUniformMatrix2x4fv = (_glUniformMatrix2x4fv)qt_gl_getProcAddress("glUniformMatrix2x4fv");
    glUniformMatrix3x2fv = (_glUniformMatrix3x2fv)qt_gl_getProcAddress("glUniformMatrix3x2fv");
    glUniformMatrix3x4fv = (_glUniformMatrix3x4fv)qt_gl_getProcAddress("glUniformMatrix3x4fv");
    glUniformMatrix4x2fv = (_glUniformMatrix4x2fv)qt_gl_getProcAddress("glUniformMatrix4x2fv");
    glUniformMatrix4x3fv = (_glUniformMatrix4x3fv)qt_gl_getProcAddress("glUniformMatrix4x3fv");

    glBindAttribLocation = (_glBindAttribLocation)qt_gl_getProcAddress("glBindAttribLocation");
    glGetAttribLocation = (_glGetAttribLocation)qt_gl_getProcAddress("glGetAttribLocation");
    glVertexAttrib1fv = (_glVertexAttrib1fv)qt_gl_getProcAddress("glVertexAttrib1fv");
    glVertexAttrib2fv = (_glVertexAttrib2fv)qt_gl_getProcAddress("glVertexAttrib2fv");
    glVertexAttrib3fv = (_glVertexAttrib3fv)qt_gl_getProcAddress("glVertexAttrib3fv");
    glVertexAttrib4fv = (_glVertexAttrib4fv)qt_gl_getProcAddress("glVertexAttrib4fv");
    glVertexAttribPointer = (_glVertexAttribPointer)qt_gl_getProcAddress("glVertexAttribPointer");
    glVertexAttribIPointer = (_glVertexAttribIPointer)qt_gl_getProcAddress("glVertexAttribIPointer");
    glDisableVertexAttribArray = (_glDisableVertexAttribArray)qt_gl_getProcAddress("glDisableVertexAttribArray");
    glEnableVertexAttribArray = (_glEnableVertexAttribArray)qt_gl_getProcAddress("glEnableVertexAttribArray");
    glVertexAttribDivisor = (_glVertexAttribDivisor)qt_gl_getProcAddress("glVertexAttribDivisor");

    glGetError = (_glGetError)qt_gl_getProcAddress("glGetError");
    glDrawArrays = (_glDrawArrays)qt_gl_getProcAddress("glDrawArrays");
    glDrawElements = (_glDrawElements)qt_gl_getProcAddress("glDrawElements");

    glGenerateMipmap = (_glGenerateMipmap)qt_gl_getProcAddress("glGenerateMipmap");

    // Buffer objects
    glBindBuffer = (_glBindBuffer)qt_gl_getProcAddress("glBindBuffer");
    glDeleteBuffers = (_glDeleteBuffers)qt_gl_getProcAddress("glDeleteBuffers");
    glGenBuffers = (_glGenBuffers)qt_gl_getProcAddress("glGenBuffers");
    glBufferData = (_glBufferData)qt_gl_getProcAddress("glBufferData");
    glBufferSubData = (_glBufferSubData)qt_gl_getProcAddress("glBufferSubData");
    glGetBufferSubData = (_glGetBufferSubData)qt_gl_getProcAddress("glGetBufferSubData");
    glGetBufferParameteriv = (_glGetBufferParameteriv)qt_gl_getProcAddress("glGetBufferParameteriv");

    glBindTexture = (_glBindTexture)qt_gl_getProcAddress("glBindTexture");
    glDepthRangef = (_glDepthRangef)qt_gl_getProcAddress("glDepthRangef");

#ifndef QX_OPENGL_ES_2_0
    // VAO objects (opengl 3.x)
    glBindVertexArray = (_glBindVertexArray)qt_gl_getProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (_glDeleteVertexArrays)qt_gl_getProcAddress("glDeleteVertexArrays");
    glGenVertexArrays = (_glGenVertexArrays)qt_gl_getProcAddress("glGenVertexArrays");
#endif

    glDrawArraysInstanced = (_glDrawArraysInstanced)qt_gl_getProcAddress("glDrawArraysInstanced");

#ifdef _WIN32
    FreeLibrary(gl_module);
#endif

    return true;
}
