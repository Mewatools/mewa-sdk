/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef STARSPROGRAM_H
#define STARSPROGRAM_H

#include "mxgpuprogram.h"

class MxMatrix;

/*
 * This program renders a torus made of triangles with procedural geometry.
 * The shader generates all geometry in the vertex shader based on gl_VertexID.
 *
 * Mouse interaction:
 * - Mouse X/Y: Rotate the torus
 * - Mouse scroll (Z): Zoom in/out
 *
 * The shader defines:
 * - TRIANGLES_SCREEN_ORIENTED: Makes triangles face the screen
 * - Comment this out in the shader to make triangles aligned with the torus surface
 *
 * Shader parameters (hardcoded in shader):
 * - Nr = 21: Number of segments around the tube
 * - NR = 64: Number of segments around the main circle
 * - R = 1.0: Major radius (main circle)
 * - r = 0.3: Minor radius (tube)
 * - rt = r * 0.1: Triangle size
 */
class StarsProgram : public MxGpuProgram
{
public:
    StarsProgram();
    virtual ~StarsProgram();

    virtual bool initialize(MxRenderer *renderer);
    void compile();

    void draw(int vertexCount);

    virtual MxGpuProgram::VaoFormat vaoFormat();
    virtual void enableAttributes();
    virtual void disableAttributes();

    // Uniform setters
    void setResolution(float width, float height);
    void setZoom(float zoom);
    void setMorphProgress(float progress); // 0.0 = torus, 1.0 = sphere
    void setGlobalSize(float size);
    void setProjection(const MxMatrix &matrix);
    void setRotations(float mouseX, float mouseY, float time);

private:
    // Uniform locations
    GLint uTimeLocation;
    GLint uResolutionLocation;
    GLint uMouseDataLocation;
    GLint uMorphProgressLocation;
    GLint uGlobalSizeLocation;
    GLint uProjectionLocation;
    GLint uRotationXZLocation;
    GLint uRotationYZLocation;

    // Dummy VAO (required for OpenGL Core Profile)
    GLuint mDummyVAO;
};

#endif // STARSPROGRAM_H
