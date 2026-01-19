/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include "simpletriangle.h"
#include "mxcompositor.h"
#include "mxcontrolpanel.h"

#include <math.h>

SimpleTriangle::SimpleTriangle()
{
}

SimpleTriangle::~SimpleTriangle()
{
}

void SimpleTriangle::renderOutput(MxCompositor &compositor)
{
    MxRenderer &renderer = compositor.renderer();
    renderer.setProgram(&pProgram);
    Q_ASSERT(pProgram.programId() > 0);

    float t = compositor.time();
    float triangleTop = 0.5f * sin(t) + 0.25;

    const GLfloat gTriangleVertices[] = {0.0f, triangleTop, -0.5f, -0.5f, 0.5f, -0.5f};
    MxGpuArray *gpuArray = renderer.uploadToGpu(pProgram.vaoFormat(), (char *)gTriangleVertices, 6 * sizeof(GLfloat));
    pProgram.enableVao(gpuArray);

    renderer.glDrawArrays(GL_TRIANGLES, 0, 3);

    renderer.checkGLError(__FILE__, __LINE__);
}

void SimpleTriangle::setupControlPanel(MxControlPanel *panel)
{
}
