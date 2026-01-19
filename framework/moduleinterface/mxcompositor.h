/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXCOMPOSITOR_H
#define MXCOMPOSITOR_H

#include "mxrenderer.h"

class MxCompositor
{
public:
    MxCompositor();
    ~MxCompositor();

    MxRenderer &renderer();
    float time() const;
    const MxVector2F &outputResolution() const;
    void setClearColor(float red, float green, float blue);

private:
    friend class AppAbstraction;

    void initializeGL();

    MxRenderer pRenderer;
    float pTime;
    MxVector2F pOutputResolution;

    MxVector4F pClearColor;
    bool pClearColorChanged;
};

#endif
