/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

#ifndef STARSMODULE_H
#define STARSMODULE_H

#include "mxmodule.h"
#include "mxcompositor.h"
#include "starsprogram.h"

class StarsModule : public MxModule
{
public:
    StarsModule();

    virtual void renderOutput(MxCompositor &compositor);

protected:
    StarsProgram pTorusProgram;

    // Mouse state for rotation calculations
    float pMouseX;
    float pMouseY;

    float pMorphProgress;
};

#endif // STARSMODULE_H
