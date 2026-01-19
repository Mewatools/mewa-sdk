/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include "appabstraction.h"

#include <stdlib.h>

AppAbstraction::AppAbstraction()
    : pNode(nullptr)
{
}

void AppAbstraction::setModule(MxModule *module)
{
    Q_ASSERT(nullptr == pNode);
    pNode = module;
}

void AppAbstraction::setupGL(int windowWidth, int windowHeight)
{
    pCompositor.initializeGL();
    onResize(windowWidth, windowHeight);
}

void AppAbstraction::onResize(int windowWidth, int windowHeight)
{
    pCompositor.pRenderer.setWindowSize(windowWidth, windowHeight);
    pCompositor.pRenderer.glViewport(0, 0, windowWidth, windowHeight);
}

void AppAbstraction::render(const float time)
{
    pCompositor.pTime = time;

    if (pCompositor.pClearColorChanged)
    {
        pCompositor.pClearColorChanged = false;
        pCompositor.pRenderer.glClearColor(pCompositor.pClearColor[0], pCompositor.pClearColor[1], pCompositor.pClearColor[2], 1.0f);
    }

    pCompositor.pRenderer.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pNode->renderOutput(pCompositor);
}

void AppAbstraction::onMousePress(const MxVector2F &position)
{

    pNode->onMousePress(position.x(), position.y(), 1);
}

void AppAbstraction::onMouseMove(const MxVector2F &position)
{

    pNode->onMouseMove(position.x(), position.y());
}
