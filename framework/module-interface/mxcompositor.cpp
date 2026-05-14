/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include "mxcompositor.h"

/**
 * @class MxCompositor
 * @brief The MxCompositor class holds the input data necessary to render a frame
 *
 * This class is available for every frame render, it provide the current time,
 * and allows the module to change the clear color.
 *
 * @see MxRenderer
 */

/**
 * @brief Constructs a new MxCompositor instance.
 *
 * Initializes the compositor with default values:
 * - Time set to 0.0f
 * - Clear color set to black (0.0f, 0.0f, 0.0f, 1.0f)
 */
MxCompositor::MxCompositor()
{
    pTime = 0.0f;
    pClearColor = MxVector4F(0.0f, 0.0f, 0.0f, 1.0f);
    pClearColorChanged = true;
}


MxCompositor::~MxCompositor()
{
}

/**
 * @brief Gets a reference to the renderer
 *
 * The renderer wraps the OpenGL functions.
 * 
 * @return Reference to the MxRenderer instance
 *
 * @see MxRenderer
 */
MxRenderer &MxCompositor::renderer()
{
    return pRenderer;
}

/**
 * @brief Gets the current time value.
 *
 * This time value is what you use to animate variables inside the module.
 *
 * @return Current time in seconds as a float
 */
float MxCompositor::time() const
{
    return pTime;
}

/**
 * @brief Gets the output resolution.
 *
 * @return Reference to the output resolution as MxVector2F
 */
const MxVector2F &MxCompositor::outputResolution() const
{
    return pOutputResolution;
}

/**
 * @brief Sets the clear color for the render target.
 *
 * The clear color is used when clearing the render buffer before each frame.
 * 
 * Its the color shown if the module renders nothing.
 * 
 * Call this function only when clear color changes.
 *
 * @param red Red component (0.0 to 1.0)
 * @param green Green component (0.0 to 1.0)
 * @param blue Blue component (0.0 to 1.0)
 */
void MxCompositor::setClearColor(float red, float green, float blue)
{
    pClearColor = MxVector4F(red, green, blue, 1.0f);
    pClearColorChanged = true;
}


void MxCompositor::initializeGL()
{
    pRenderer.initialize();
}
