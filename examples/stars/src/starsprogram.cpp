/***************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include "starsprogram.h"
#include "mxrenderer.h"
#include "mxmatrix.h"
#include <cmath>

StarsProgram::StarsProgram()
{
    uTimeLocation = -1;
    uResolutionLocation = -1;
    uMouseDataLocation = -1;
    uMorphProgressLocation = -1;
    uProjectionLocation = -1;
    uRotationXZLocation = -1;
    uRotationYZLocation = -1;
    mDummyVAO = 0;
}

StarsProgram::~StarsProgram()
{
    if (pRenderer && mProgramId)
        pRenderer->glDeleteProgram(mProgramId);

    if (pRenderer && mDummyVAO)
        pRenderer->glDeleteVertexArrays(1, &mDummyVAO);
}

bool StarsProgram::initialize(MxRenderer *renderer)
{
    Q_ASSERT(NULL == pRenderer);
    pRenderer = renderer;

    compile();
    return (mProgramId != 0);
}

void StarsProgram::compile()
{
    // Vertex shader - star sprites generated procedurally per gl_VertexID
    GLuint vshader = pRenderer->glCreateShader(GL_VERTEX_SHADER);
    const char *vsrc =
        "#version 300 es\n"
        "precision highp float;\n"
        "\n"
        "#define TAU 6.28318530718\n"
        "\n"
        "uniform float iTime;\n"
        "uniform vec2 iResolution;\n"
        "uniform float iMouseZoom;\n"
        "uniform float iMorphProgress;\n"
        "uniform float iGlobalSize;\n"
        "uniform mat4 iProjection;\n"
        "\n"
        "out vec3 vertNormal;\n"
        "out vec2 vertTexCoord;\n"
        "out vec3 vertPos;\n"
        "out vec3 vertColor;\n"
        "\n"
        "float hashf(float n) { return fract(sin(n) * 43758.5453123); }\n"
        "\n"
        "void mainGeom( out vec4 vertCoord, out vec4 vertAttrib[3], int vertIndex )\n"
        "{\n"
        "    int starIndex = vertIndex / 3;\n"
        "    float si = float(starIndex);\n"
        "    float r0 = hashf(si + 1.0);\n"
        "    float r1 = hashf(si + 2.0);\n"
        "    float r2 = hashf(si + 3.0);\n"
        "    float r3 = hashf(si + 4.0);\n"
        "\n"
        "    float spreadX = 12.0;\n"
        "    float spreadY = 7.0;\n"
        "    float x = (r0 * 2.0 - 1.0) * spreadX;\n"
        "    float y = (r1 * 2.0 - 1.0) * spreadY;\n"
        "\n"
        "    // depth and forward motion\n"
        "    float zRange = 200.0;\n"
        "    float baseZ = r2 * zRange;\n"
        "    float speed = 15.0 + r3 * 40.0;\n"
        "    float z = -mod(baseZ - iTime * speed, zRange);\n"
        "\n"
        "    // animated lateral drift + swirl for cinematic motion\n"
        "    float ang = iTime * (1.0 + r3 * 2.5);\n"
        "    float driftAmp = mix(0.05, 3.0, r0) * (0.5 + 0.5 * sin(iTime * 0.3 + si));\n"
        "    float swirl = 0.6 * sin((baseZ / zRange) * TAU + iTime * 0.12);\n"
        "    x += sin(ang + r1 * TAU) * driftAmp + swirl;\n"
        "    y += cos(ang * 0.7 + r2 * TAU) * (driftAmp * 0.6) + 0.5 * swirl;\n"
        "\n"
        "    float sizeBase = mix(0.12, 1.2, 1.0 - (baseZ / zRange));\n"
        "    float size = sizeBase * (0.8 + 0.6 * iMorphProgress) * iGlobalSize;\n"
        "\n"
        "    int localV = vertIndex % 3;\n"
        "    vec2 triOffsets[3];\n"
        "    triOffsets[0] = vec2(0.0, 1.0);\n"
        "    triOffsets[1] = vec2(-0.866, -0.5);\n"
        "    triOffsets[2] = vec2(0.866, -0.5);\n"
        "    vec2 off = triOffsets[localV] * size;\n"
        "\n"
        "    vec3 p = vec3(x + off.x, y + off.y, z);\n"
        "\n"
        "    float twinkle = 0.7 + 0.3 * sin(iTime * (2.0 + r3 * 5.0) + si);\n"
        "    vec3 baseColor = vec3(0.6 + 0.4 * r0, 0.7 * r1 + 0.3, 0.8 * r2 + 0.2) * twinkle;\n"
        "\n"
        "    vertCoord = iProjection * vec4(p, 1.0);\n"
        "    vertAttrib[0] = vec4(0.0, 0.0, 1.0, 1.0);\n"
        "    // barycentric coordinates per vertex so fragment shader can build a star shape\n"
        "    vec2 bc[3];\n"
        "    bc[0] = vec2(0.0, 0.0);\n"
        "    bc[1] = vec2(1.0, 0.0);\n"
        "    bc[2] = vec2(0.0, 1.0);\n"
        "    vertAttrib[1] = vec4(bc[localV], 0.0, 0.0);\n"
        "    vertAttrib[2] = vec4(p, 1.0);\n"
        "}\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    vec4 vertAttrib[3];\n"
        "    vec4 vertCoord;\n"
        "    mainGeom( vertCoord, vertAttrib, gl_VertexID );\n"
        "    gl_Position = vertCoord;\n"
        "    vertNormal = normalize(vertAttrib[0].xyz);\n"
        "    vertPos = vertAttrib[2].xyz;\n"
        "    float si = float(gl_VertexID / 3);\n"
        "    float r0 = fract(sin((si + 1.0)) * 43758.5453123);\n"
        "    float r1 = fract(sin((si + 2.0)) * 43758.5453123);\n"
        "    float r2 = fract(sin((si + 3.0)) * 43758.5453123);\n"
        "    float tw = 0.7 + 0.3 * sin(iTime * (2.0 + r2 * 5.0) + si);\n"
        "    vertColor = vec3(0.6 + 0.4 * r0, 0.7 * r1 + 0.3, 0.8 * r2 + 0.2) * tw;\n"
        "    vertTexCoord = vertAttrib[1].xy;\n"
        "}\n";

    pRenderer->glShaderSource(vshader, 1, &vsrc, NULL);
    pRenderer->glCompileShader(vshader);
    GLint compiled;
    pRenderer->glGetShaderiv(vshader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE)
    {
        GLint infoLogLength;
        pRenderer->glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *errMsg = new char[infoLogLength + 1];
        pRenderer->glGetShaderInfoLog(vshader, infoLogLength, NULL, errMsg);
        qDebug("MxTorusTrianglesProgram vertex shader compilation error: %s", errMsg);
        delete[] errMsg;
    }
    else
    {
        qDebug("MxTorusTrianglesProgram vertex shader compiled successfully");
    }

    // Fragment shader - simplified minimal version
    GLuint fshader = pRenderer->glCreateShader(GL_FRAGMENT_SHADER);
    const char *fsrc =
        "#version 300 es\n"
        "precision mediump float;\n"
        "\n"
        "in vec3 vertNormal;\n"
        "in vec2 vertTexCoord;\n"
        "in vec3 vertPos;\n"
        "in vec3 vertColor;\n"
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "void mainFragment( out vec4 fragColor, vec4 fragCoord, vec3 N, vec2 bc, vec3 pos, vec3 col )\n"
        "{\n"
        "    // bc holds barycentric-like coords interpolated across the triangle\n"
        "    vec2 center = vec2(1.0/3.0, 1.0/3.0);\n"
        "    vec2 d = bc - center;\n"
        "    float r = length(d);\n"
        "    float a = atan(d.y, d.x);\n"
        "\n"
        "    // spikes: how many star points\n"
        "    float spikes = 6.0;\n"
        "    float spike = 0.5 + 0.5 * cos(a * spikes);\n"
        "\n"
        "    // radial shape modulated by spikes -> star silhouette\n"
        "    float shape = smoothstep(0.14, 0.02, r * (0.8 + 1.2 * spike));\n"
        "\n"
        "    // core brightness and soft glow\n"
        "    float core = pow(shape, 1.2);\n"
        "    vec3 color = col * (0.6 + 0.8 * core + 0.6 * spike);\n"
        "    float glow = smoothstep(0.5, 0.0, r * (0.6 + spike * 0.8));\n"
        "    color += vec3(1.0, 0.9, 0.7) * 0.5 * glow;\n"
        "\n"
        "    // depth fog to soften distant stars\n"
        "    float fogFactor = exp(-length(pos) * 0.02);\n"
        "    vec3 fogColor = vec3(0.02, 0.02, 0.03);\n"
        "    color = mix(fogColor, color, clamp(fogFactor, 0.0, 1.0));\n"
        "\n"
        "    fragColor = vec4(color, shape);\n"
        "}\n"
        "\n"
        "void main()\n"
        "{\n"
        "    mainFragment( fragColor, gl_FragCoord, vertNormal, vertTexCoord, vertPos, vertColor );\n"
        "}\n";

    pRenderer->glShaderSource(fshader, 1, &fsrc, NULL);
    pRenderer->glCompileShader(fshader);
    pRenderer->glGetShaderiv(fshader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE)
    {
        GLint infoLogLength;
        pRenderer->glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *errMsg = new char[infoLogLength + 1];
        pRenderer->glGetShaderInfoLog(fshader, infoLogLength, NULL, errMsg);
        qDebug("MxTorusTrianglesProgram fragment shader compilation error: %s", errMsg);
        delete[] errMsg;
    }
    else
    {
        qDebug("MxTorusTrianglesProgram fragment shader compiled successfully");
    }

    // Link program
    mProgramId = pRenderer->glCreateProgram();
    pRenderer->glAttachShader(mProgramId, vshader);
    pRenderer->glAttachShader(mProgramId, fshader);
    pRenderer->glLinkProgram(mProgramId);

    GLint linkStatus = 0;
    pRenderer->glGetProgramiv(mProgramId, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint infoLogLength;
        pRenderer->glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *errMsg = new char[infoLogLength + 1];
        pRenderer->glGetProgramInfoLog(mProgramId, infoLogLength, NULL, errMsg);
        qDebug("MxTorusTrianglesProgram link error: %s", errMsg);
        delete[] errMsg;
    }
    else
    {
        qDebug("MxTorusTrianglesProgram linked successfully");
    }

    // Get uniform locations
    uTimeLocation = pRenderer->glGetUniformLocation(mProgramId, "iTime");
    uResolutionLocation = pRenderer->glGetUniformLocation(mProgramId, "iResolution");
    uMouseDataLocation = pRenderer->glGetUniformLocation(mProgramId, "iMouseZoom");
    uMorphProgressLocation = pRenderer->glGetUniformLocation(mProgramId, "iMorphProgress");
    uGlobalSizeLocation = pRenderer->glGetUniformLocation(mProgramId, "iGlobalSize");
    uProjectionLocation = pRenderer->glGetUniformLocation(mProgramId, "iProjection");
    uRotationXZLocation = pRenderer->glGetUniformLocation(mProgramId, "iRotationXZ");
    uRotationYZLocation = pRenderer->glGetUniformLocation(mProgramId, "iRotationYZ");

    qDebug("Uniform locations - iTime:%d iResolution:%d iMouseZoom:%d iMorphProgress:%d iProjection:%d iRotationXZ:%d iRotationYZ:%d",
           uTimeLocation, uResolutionLocation, uMouseDataLocation, uMorphProgressLocation, uProjectionLocation, uRotationXZLocation, uRotationYZLocation);

    pRenderer->checkGLError(__FILE__, __LINE__);

    // Clean up shaders
    pRenderer->glDetachShader(mProgramId, vshader);
    pRenderer->glDetachShader(mProgramId, fshader);
    pRenderer->glDeleteShader(vshader);
    pRenderer->glDeleteShader(fshader);

    // Create a dummy VAO (required for OpenGL Core Profile even with no vertex attributes)
    pRenderer->glGenVertexArrays(1, &mDummyVAO);
    qDebug("Created dummy VAO: %d", mDummyVAO);
}

void StarsProgram::draw(int vertexCount)
{
    // Bind dummy VAO (required for OpenGL Core Profile)
    if (mDummyVAO)
    {
        pRenderer->glBindVertexArray(mDummyVAO);
    }

    pRenderer->glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    pRenderer->checkGLError(__FILE__, __LINE__);

    // Unbind VAO
    if (mDummyVAO)
    {
        pRenderer->glBindVertexArray(0);
    }
}

MxGpuProgram::VaoFormat StarsProgram::vaoFormat()
{
    // This program doesn't use a VBO - vertices are generated in the shader
    return MxGpuProgram::Custom;
}

void StarsProgram::enableAttributes()
{
    // No attributes needed - vertices are generated procedurally in the vertex shader
}

void StarsProgram::disableAttributes()
{
    // No attributes to disable
}

void StarsProgram::setResolution(float width, float height)
{
    if (uResolutionLocation >= 0)
        pRenderer->glUniform2f(uResolutionLocation, width, height);
}

void StarsProgram::setGlobalSize(float size)
{
    if (uGlobalSizeLocation >= 0)
    {
        pRenderer->glUniform1f(uGlobalSizeLocation, size);
    }
}

void StarsProgram::setZoom(float zoom)
{
    if (uMouseDataLocation >= 0)
    {
        // Calculate zoom offset on CPU instead of in vertex shader
        // Original shader calculation: 2.*exp2(-iMouseZoom)
        float zoomOffset = 2.0f * exp2f(-(zoom / 5000.0f));
        pRenderer->glUniform1f(uMouseDataLocation, zoomOffset);
    }
}

void StarsProgram::setMorphProgress(float progress)
{
    if (uMorphProgressLocation >= 0)
    {
        // Clamp progress to [0.0, 1.0] range
        float clampedProgress = progress < 0.0f ? 0.0f : (progress > 1.0f ? 1.0f : progress);
        pRenderer->glUniform1f(uMorphProgressLocation, clampedProgress);
    }
}

void StarsProgram::setProjection(const MxMatrix &matrix)
{
    if (uProjectionLocation >= 0)
    {
        pRenderer->glUniformMatrix4fv(uProjectionLocation, 1, GL_FALSE, matrix.constData());
    }
}

void StarsProgram::setRotations(float mouseX, float mouseY, float time)
{
    // Set time uniform
    if (uTimeLocation >= 0)
    {
        pRenderer->glUniform1f(uTimeLocation, time);
    }

    // Calculate rotation angles based on mouse and time
    const float TAU = 3.14159265358979323846f * 2.0f;

    // XZ rotation angle
    float angleXZ = mouseX / 600.0f + time * 0.3f;
    float cosXZ = cosf(angleXZ);
    float sinXZ = sinf(angleXZ);

    // YZ rotation angle (note the negative mouseY)
    float angleYZ = -mouseY / 600.0f + time * 0.1f;
    float cosYZ = cosf(angleYZ);
    float sinYZ = sinf(angleYZ);

    // Set rotation matrices (column-major order for OpenGL)
    if (uRotationXZLocation >= 0)
    {
        float rotXZ[4] = {cosXZ, sinXZ, -sinXZ, cosXZ};
        pRenderer->glUniformMatrix2fv(uRotationXZLocation, 1, GL_FALSE, rotXZ);
    }

    if (uRotationYZLocation >= 0)
    {
        float rotYZ[4] = {cosYZ, sinYZ, -sinYZ, cosYZ};
        pRenderer->glUniformMatrix2fv(uRotationYZLocation, 1, GL_FALSE, rotYZ);
    }
}
