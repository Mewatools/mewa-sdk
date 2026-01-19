/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

#ifndef APPABSTRACTION_H
#define APPABSTRACTION_H

#include "mxcompositor.h"
#include "mxmodule.h"

class AppAbstraction
{
public:
    AppAbstraction();

    void setModule(MxModule *module);

    void setupGL(int windowWidth, int windowHeight);
    void onResize(int windowWidth, int windowHeight);
    void render(const float time);

    void onMousePress(const MxVector2F &position);
    void onMouseMove(const MxVector2F &position);

    MxCompositor pCompositor;
    MxModule *pNode;
};

#endif // APPABSTRACTION_H
