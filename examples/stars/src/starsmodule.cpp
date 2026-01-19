/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

#include "starsmodule.h"

#include <cmath>

StarsModule::StarsModule()
    : pMouseX(0.0f), pMouseY(0.0f)
{
}

void StarsModule::renderOutput(MxCompositor &compositor)
{
    MxRenderer &renderer = compositor.renderer();
    const float time = compositor.time();

    // Cinematic animation: enable depth testing and keep blending for soft edges
    renderer.glEnable(GL_DEPTH_TEST);
    renderer.setBlending(MxRenderer::BlendingImages);

    // Update animation parameters driven by time (movie-like motion)
    // Smoothly rotate the object using low-frequency oscillations
    pMouseX = 300.0f * sinf(time * 0.18f) + 40.0f * sinf(time * 0.7f);
    pMouseY = 200.0f * cosf(time * 0.14f) + 30.0f * cosf(time * 0.9f);

    // Morph progress cycles slowly between torus and sphere
    pMorphProgress = 0.5f + 0.5f * sinf(time * 0.22f);

    // Subtle cinematic zoom in/out
    float zoom = 300.0f + 150.0f * sinf(time * 0.12f + 1.234f);

    // Enable the torus shader program
    renderer.setProgram(&pTorusProgram);

    const MxVector2I &viewSize = renderer.windowSize();
    const float width = static_cast<float>(viewSize.x());
    const float height = static_cast<float>(viewSize.y());

    // Set shader uniforms
    pTorusProgram.setResolution(width, height);

    // Calculate projection matrix on CPU (a slightly wide frustum for cinematic feel)
    float aspect = height / width;
    MxMatrix projection;
    projection.setToIdentity();
    projection.frustum(-0.12f, 0.12f, -0.12f * aspect, 0.12f * aspect, 0.1f, 200.0f);
    pTorusProgram.setProjection(projection);

    pTorusProgram.setGlobalSize(1.2);

    // Set rotation matrices and time (pre-calculated on CPU)
    pTorusProgram.setRotations(pMouseX, pMouseY, time);

    // Set zoom and morph progress
    pTorusProgram.setZoom(zoom);
    pTorusProgram.setMorphProgress(pMorphProgress);

    // Draw the geometry as many small star-triangles (3 vertices per star)
    const int STAR_COUNT = 600;
    int vertexCount = STAR_COUNT * 3;
    pTorusProgram.draw(vertexCount);

    // Restore GL state
    renderer.glDisable(GL_DEPTH_TEST);
}
