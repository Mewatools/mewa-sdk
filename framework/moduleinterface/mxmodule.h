/***************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXMODULE_H
#define MXMODULE_H

#include "mxvector.h"

class MxCompositor;
class MxControlPanel;

class MxModule
{
public:
    MxModule();

    virtual void onMousePress(int x, int y, unsigned int button) {}

    virtual void onMouseMove(int x, int y) {}

    virtual void onMouseRelease(int x, int y) {}

    virtual void renderOutput(MxCompositor &compositor) = 0;

    virtual void setupControlPanel(MxControlPanel *panel) {}
};

#endif // MXMODULE_H
