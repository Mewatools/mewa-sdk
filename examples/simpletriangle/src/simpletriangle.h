/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef SIMPLETRIANGLE_H
#define SIMPLETRIANGLE_H

#include "mxmodule.h"
#include "triangleprogram.h"

class SimpleTriangle : public MxModule
{
public:
    SimpleTriangle();
    virtual ~SimpleTriangle();

    virtual void renderOutput(MxCompositor &compositor);
    virtual void setupControlPanel(MxControlPanel *panel);

private:
    TriangleProgram pProgram;
};

#endif // SIMPLETRIANGLE_H
