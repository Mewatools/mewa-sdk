/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

#ifndef MXOPENGLFUNCTIONS_H
#define MXOPENGLFUNCTIONS_H

#if defined(__linux__)
#include <GL/gl.h>
#include <GL/glx.h>
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

/*#elif defined(_WIN32)
#ifdef QX_USING_QT
#include <qopengl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif*/

#elif defined(QX_PLATFORM_MACOSX)
#include <OpenGL/gl.h>
// #import <OpenGL/OpenGL.h>
#endif

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
#define GL_NUM_EXTENSIONS 0x821D

/*
// APIENTRY is windows only
#ifndef QX_PLATFORM_MACOSX
# ifndef APIENTRYP
#   ifdef APIENTRY
#     define APIENTRYP APIENTRY *
#   else
#     define APIENTRY
#     define APIENTRYP *
#   endif
# endif
#else
# define APIENTRY
# define APIENTRYP *
#endif
*/
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#define APIENTRY
#define APIENTRYP *
#endif

#ifdef _WIN32
#include <cstddef>
#include <Windows.h> // HMODULE
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef ptrdiff_t GLsizeiptr;

/* BeginMode */
#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_QUADS 0x0007
#define GL_QUAD_STRIP 0x0008
#define GL_POLYGON 0x0009

/* BlendingFactorDest */
#define GL_ZERO 0
#define GL_ONE 1
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* Boolean */
#define GL_TRUE 1
#define GL_FALSE 0

#define GL_UNPACK_ALIGNMENT 0x0CF5

/* DataType */
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_2_BYTES 0x1407
#define GL_3_BYTES 0x1408
#define GL_4_BYTES 0x1409
#define GL_DOUBLE 0x140A

/* ErrorCode */
#define GL_NO_ERROR 0
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_OUT_OF_MEMORY 0x0505

/* TextureMagFilter */
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_LINEAR_MIPMAP_LINEAR 0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803

/* PixelCopyType */
#define GL_COLOR 0x1800
#define GL_DEPTH 0x1801
#define GL_STENCIL 0x1802

/* PixelFormat */
#define GL_COLOR_INDEX 0x1900
#define GL_STENCIL_INDEX 0x1901
#define GL_DEPTH_COMPONENT 0x1902
#define GL_RED 0x1903
#define GL_GREEN 0x1904
#define GL_BLUE 0x1905
#define GL_ALPHA 0x1906
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_LUMINANCE 0x1909
#define GL_LUMINANCE_ALPHA 0x190A

#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_COLOR_BUFFER_BIT 0x00004000

#define GL_LINE_SMOOTH 0x0B20

#define GL_BLEND 0x0BE2
#define GL_TEXTURE_2D 0x0DE1
#define GL_CULL_FACE 0x0B44
#define GL_DEPTH_TEST 0x0B71
#define GL_STENCIL_TEST 0x0B90
#define GL_SCISSOR_TEST 0x0C11
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_KEEP 0x1E00
#define GL_INVERT 0x150A
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207

#define GL_TEXTURE_WRAP_R 0x8072
#define GL_RG 0x8227
#define GL_R8 0x8229
#define GL_R32F 0x822E
#define GL_RG32F 0x8230
#define GL_RGBA32F 0x8814
#define GL_RGB32F 0x8815
#define GL_TEXTURE_2D_ARRAY 0x8C1A

#endif

#ifndef GL_ARB_vertex_buffer_object
#include <cstddef>
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
#endif

typedef void(APIENTRY *_glBlendFunc)(GLenum sfactor, GLenum dfactor);
typedef void(APIENTRY *_glClear)(GLbitfield mask);
typedef void(APIENTRY *_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void(APIENTRY *_glClearStencil)(GLint s);
typedef void(APIENTRY *_glEnable)(GLenum cap);
typedef void(APIENTRY *_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

typedef void(APIENTRY *_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void(APIENTRY *_glStencilOp)(GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void(APIENTRY *_glStencilMask)(GLuint mask);
typedef void(APIENTRY *_glStencilFunc)(GLenum func, GLint ref, GLuint mask);

typedef void(APIENTRY *_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void(APIENTRY *_glDisable)(GLenum cap);
typedef void(APIENTRY *_glBlendEquation)(GLenum mode);

typedef void(APIENTRY *_glLineWidth)(GLfloat width);

typedef void(APIENTRY *_glMultiTexCoord4f)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void(APIENTRY *_glActiveStencilFaceEXT)(GLenum);
typedef void(APIENTRY *_glActiveTexture)(GLenum);

typedef void(APIENTRY *_glGenTextures)(GLsizei n, GLuint *textures);
typedef void(APIENTRY *_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void(APIENTRY *_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);

typedef void(APIENTRY *_glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *data);
typedef void(APIENTRY *_glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);

typedef void(APIENTRY *_glPixelStorei)(GLenum pname, GLint param);

typedef void(APIENTRY *_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
typedef void(APIENTRY *_glDeleteTextures)(GLsizei n, const GLuint *textures);
typedef void(APIENTRY *_glGetIntegerv)(GLenum pname, GLint *params);

typedef void(APIENTRY *_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
typedef void(APIENTRY *_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat *params);
typedef void(APIENTRY *_glTexParameteri)(GLenum target, GLenum pname, GLint param);
typedef void(APIENTRY *_glTexParameteriv)(GLenum target, GLenum pname, const GLint *params);

// GLSL
typedef GLuint(APIENTRY *_glCreateShader)(GLenum);
typedef void(APIENTRY *_glShaderSource)(GLuint, GLsizei, const char **, const GLint *);
typedef void(APIENTRY *_glShaderBinary)(GLint, const GLuint *, GLenum, const void *, GLint);
typedef void(APIENTRY *_glCompileShader)(GLuint);
typedef void(APIENTRY *_glDeleteShader)(GLuint);
typedef GLboolean(APIENTRY *_glIsShader)(GLuint);

typedef GLuint(APIENTRY *_glCreateProgram)();
typedef void(APIENTRY *_glAttachShader)(GLuint, GLuint);
typedef void(APIENTRY *_glDetachShader)(GLuint, GLuint);
typedef void(APIENTRY *_glLinkProgram)(GLuint);
typedef void(APIENTRY *_glUseProgram)(GLuint);
typedef void(APIENTRY *_glDeleteProgram)(GLuint);
typedef GLboolean(APIENTRY *_glIsProgram)(GLuint);

typedef void(APIENTRY *_glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, char *);
typedef void(APIENTRY *_glGetShaderiv)(GLuint, GLenum, GLint *);
typedef void(APIENTRY *_glGetShaderSource)(GLuint, GLsizei, GLsizei *, char *);
typedef void(APIENTRY *_glGetProgramiv)(GLuint, GLenum, GLint *);
typedef void(APIENTRY *_glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, char *);

typedef GLuint(APIENTRY *_glGetUniformLocation)(GLuint, const char *);
typedef void(APIENTRY *_glUniform4fv)(GLint, GLsizei, const GLfloat *);
typedef void(APIENTRY *_glUniform3fv)(GLint, GLsizei, const GLfloat *);
typedef void(APIENTRY *_glUniform2fv)(GLint, GLsizei, const GLfloat *);
typedef void(APIENTRY *_glUniform1fv)(GLint, GLsizei, const GLfloat *);
typedef void(APIENTRY *_glUniform1f)(GLint, GLfloat);
typedef void(APIENTRY *_glUniform2f)(GLint, GLfloat, GLfloat);
typedef void(APIENTRY *_glUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
typedef void(APIENTRY *_glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void(APIENTRY *_glUniform1i)(GLint, GLint);
typedef void(APIENTRY *_glUniform1iv)(GLint, GLsizei, const GLint *);
typedef void(APIENTRY *_glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
typedef void(APIENTRY *_glUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);

typedef void(APIENTRY *_glBindAttribLocation)(GLuint, GLuint, const char *);
typedef GLint(APIENTRY *_glGetAttribLocation)(GLuint, const char *);
typedef void(APIENTRY *_glVertexAttrib1fv)(GLuint, const GLfloat *);
typedef void(APIENTRY *_glVertexAttrib2fv)(GLuint, const GLfloat *);
typedef void(APIENTRY *_glVertexAttrib3fv)(GLuint, const GLfloat *);
typedef void(APIENTRY *_glVertexAttrib4fv)(GLuint, const GLfloat *);
typedef void(APIENTRY *_glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *);
typedef void(APIENTRY *_glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const GLvoid *);
typedef void(APIENTRY *_glDisableVertexAttribArray)(GLuint);
typedef void(APIENTRY *_glEnableVertexAttribArray)(GLuint);

typedef void(APIENTRY *_glVertexAttribDivisor)(GLuint, GLuint);

typedef void(APIENTRY *_glGetProgramBinaryOES)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
typedef void(APIENTRY *_glProgramBinaryOES)(GLuint, GLenum, const void *, GLint);

typedef GLenum(APIENTRY *_glGetError)(void);

// Needed for GL2 engine:
typedef void(APIENTRY *_glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
// typedef void (APIENTRY *_glActiveTexture) (GLenum);
typedef void(APIENTRY *_glBlendColor)(GLclampf, GLclampf, GLclampf, GLclampf);
typedef void(APIENTRY *_glDrawArrays)(GLenum mode, GLint first, GLsizei count);
typedef void(APIENTRY *_glDrawElements)(GLenum, GLsizei, GLenum, const void *);

// EXT_GL_framebuffer_object
typedef GLboolean(APIENTRY *_glIsRenderbuffer)(GLuint renderbuffer);
typedef void(APIENTRY *_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
typedef void(APIENTRY *_glDeleteRenderbuffers)(GLsizei n, const GLuint *renderbuffers);
typedef void(APIENTRY *_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
typedef void(APIENTRY *_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void(APIENTRY *_glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint *params);
typedef GLboolean(APIENTRY *_glIsFramebuffer)(GLuint framebuffer);
typedef void(APIENTRY *_glBindFramebuffer)(GLenum target, GLuint framebuffer);
typedef void(APIENTRY *_glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers);
typedef void(APIENTRY *_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
typedef GLenum(APIENTRY *_glCheckFramebufferStatus)(GLenum target);
typedef void(APIENTRY *_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget,
                                                GLuint texture, GLint level);
typedef void(APIENTRY *_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget,
                                                   GLuint renderbuffer);
typedef void(APIENTRY *_glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname,
                                                               GLint *params);
typedef void(APIENTRY *_glGenerateMipmap)(GLenum target);

// Buffer objects
typedef void(APIENTRY *_glBindBuffer)(GLenum, GLuint);
typedef void(APIENTRY *_glDeleteBuffers)(GLsizei, const GLuint *);
typedef void(APIENTRY *_glGenBuffers)(GLsizei, GLuint *);
typedef void(APIENTRY *_glBufferData)(GLenum, GLsizeiptrARB, const GLvoid *, GLenum);
typedef void(APIENTRY *_glBufferSubData)(GLenum, GLintptrARB, GLsizeiptrARB, const GLvoid *);
typedef void(APIENTRY *_glGetBufferSubData)(GLenum, GLintptrARB, GLsizeiptrARB, GLvoid *);
typedef void(APIENTRY *_glGetBufferParameteriv)(GLenum, GLenum, GLint *);
typedef void(APIENTRY *_glDepthRangef)(GLclampf near, GLclampf far);
typedef void(APIENTRY *_glBindTexture)(GLenum target, GLuint texture);

#ifndef QX_OPENGL_ES_2_0
// VAO objects (opengl 3.x)
typedef void(APIENTRY *_glBindVertexArray)(GLuint);
typedef void(APIENTRY *_glDeleteVertexArrays)(GLsizei, const GLuint *);
typedef void(APIENTRY *_glGenVertexArrays)(GLsizei, GLuint *);
#endif

// opengl 3.1 and openGL ES 3
typedef void(APIENTRY *_glDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei);

class MxOpenGLFunctions
{
public:
#ifdef _WIN32
    HMODULE gl_module;
#endif
    void *qx_getProcAddress(const char *name);
    void *qx_gl_getProcAddress_search(const char *name1, const char *name2, const char *name3);

    MxOpenGLFunctions();
    virtual ~MxOpenGLFunctions() {}

    bool init();

    /*#ifdef QX_PLATFORM_ANDROID
        enum GLExtensions {
            MultisampledRenderToTexture = 0x01,
        };

        static int supportedExtensions()
        {
            GLExtensions extensions = 0x0;
            const GLubyte* extensions_string = glGetString(GL_EXTENSIONS);
            // extensions are separated by space
            extensionList = ...;
            if( extensionList.contains("GL_EXT_multisampled_render_to_texture") ) {
                extensions |= MultisampledRenderToTexture;
                qx_glFramebufferTexture2DMultisample = (_glFramebufferTexture2DMultisample) eglGetProcAddress("glFramebufferTexture2DMultisampleEXT");
            }

            // ...

            return extensions;
        }

    #endif*/

    // static QxGLExtensions *sExtensionsInstance;

    _glBlendFunc glBlendFunc;
    _glClear glClear;
    _glClearColor glClearColor;
    _glClearStencil glClearStencil;
    _glEnable glEnable;
    _glViewport glViewport;

    _glColorMask glColorMask;
    _glStencilOp glStencilOp;
    _glStencilMask glStencilMask;
    _glStencilFunc glStencilFunc;

    _glScissor glScissor;
    _glDisable glDisable;
    _glBlendEquation glBlendEquation;

    _glLineWidth glLineWidth;

    _glActiveStencilFaceEXT glActiveStencilFaceEXT;
    _glMultiTexCoord4f glMultiTexCoord4f;
    _glActiveTexture glActiveTexture;

    _glGenTextures glGenTextures;
    _glTexImage2D glTexImage2D;
    _glTexSubImage2D glTexSubImage2D;

    _glTexImage3D glTexImage3D;
    _glTexSubImage3D glTexSubImage3D;

    _glPixelStorei glPixelStorei;
    _glReadPixels glReadPixels;
    _glDeleteTextures glDeleteTextures;
    _glGetIntegerv glGetIntegerv;

    _glTexParameterf glTexParameterf;
    _glTexParameterfv glTexParameterfv;
    _glTexParameteri glTexParameteri;
    _glTexParameteriv glTexParameteriv;

    // GLSL definitions
    _glCreateShader glCreateShader;
    _glShaderSource glShaderSource;
    _glShaderBinary glShaderBinary;
    _glCompileShader glCompileShader;
    _glDeleteShader glDeleteShader;
    _glIsShader glIsShader;

    _glCreateProgram glCreateProgram;
    _glAttachShader glAttachShader;
    _glDetachShader glDetachShader;
    _glLinkProgram glLinkProgram;
    _glUseProgram glUseProgram;
    _glDeleteProgram glDeleteProgram;
    _glIsProgram glIsProgram;

    _glGetShaderInfoLog glGetShaderInfoLog;
    _glGetShaderiv glGetShaderiv;
    _glGetShaderSource glGetShaderSource;
    _glGetProgramiv glGetProgramiv;
    _glGetProgramInfoLog glGetProgramInfoLog;

    _glGetUniformLocation glGetUniformLocation;
    _glUniform4fv glUniform4fv;
    _glUniform3fv glUniform3fv;
    _glUniform2fv glUniform2fv;
    _glUniform1fv glUniform1fv;
    _glUniform1f glUniform1f;
    _glUniform2f glUniform2f;
    _glUniform3f glUniform3f;
    _glUniform4f glUniform4f;
    _glUniform1i glUniform1i;
    _glUniform1iv glUniform1iv;
    _glUniformMatrix2fv glUniformMatrix2fv;
    _glUniformMatrix3fv glUniformMatrix3fv;
    _glUniformMatrix4fv glUniformMatrix4fv;
    _glUniformMatrix2x3fv glUniformMatrix2x3fv;
    _glUniformMatrix2x4fv glUniformMatrix2x4fv;
    _glUniformMatrix3x2fv glUniformMatrix3x2fv;
    _glUniformMatrix3x4fv glUniformMatrix3x4fv;
    _glUniformMatrix4x2fv glUniformMatrix4x2fv;
    _glUniformMatrix4x3fv glUniformMatrix4x3fv;

    _glBindAttribLocation glBindAttribLocation;
    _glGetAttribLocation glGetAttribLocation;
    _glVertexAttrib1fv glVertexAttrib1fv;
    _glVertexAttrib2fv glVertexAttrib2fv;
    _glVertexAttrib3fv glVertexAttrib3fv;
    _glVertexAttrib4fv glVertexAttrib4fv;
    _glVertexAttribPointer glVertexAttribPointer;
    _glVertexAttribIPointer glVertexAttribIPointer;
    _glDisableVertexAttribArray glDisableVertexAttribArray;
    _glEnableVertexAttribArray glEnableVertexAttribArray;

    _glVertexAttribDivisor glVertexAttribDivisor;
    _glGetError glGetError;
    _glDrawArrays glDrawArrays;
    _glDrawElements glDrawElements;

    // FBOs
    _glIsRenderbuffer glIsRenderbuffer;
    _glBindRenderbuffer glBindRenderbuffer;
    _glDeleteRenderbuffers glDeleteRenderbuffers;
    _glGenRenderbuffers glGenRenderbuffers;
    _glRenderbufferStorage glRenderbufferStorage;
    _glGetRenderbufferParameteriv glGetRenderbufferParameteriv;
    _glIsFramebuffer glIsFramebuffer;
    _glBindFramebuffer glBindFramebuffer;
    _glDeleteFramebuffers glDeleteFramebuffers;
    _glGenFramebuffers glGenFramebuffers;
    _glCheckFramebufferStatus glCheckFramebufferStatus;
    _glFramebufferTexture2D glFramebufferTexture2D;
    _glFramebufferRenderbuffer glFramebufferRenderbuffer;
    _glGetFramebufferAttachmentParameteriv glGetFramebufferAttachmentParameteriv;
    _glGenerateMipmap glGenerateMipmap;

    // Buffer objects
    _glBindBuffer glBindBuffer;
    _glDeleteBuffers glDeleteBuffers;
    _glGenBuffers glGenBuffers;
    _glBufferData glBufferData;
    _glBufferSubData glBufferSubData;
    _glGetBufferSubData glGetBufferSubData;
    _glGetBufferParameteriv glGetBufferParameteriv;

    _glBindTexture glBindTexture;

    _glDepthRangef glDepthRangef;

#ifndef QX_OPENGL_ES_2_0
    // VAO objects (opengl 3.x)
    _glBindVertexArray glBindVertexArray;
    _glDeleteVertexArrays glDeleteVertexArrays;
    _glGenVertexArrays glGenVertexArrays;
#endif

    _glDrawArraysInstanced glDrawArraysInstanced;
};

#endif
