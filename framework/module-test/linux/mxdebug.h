/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXDEBUG_H
#define MXDEBUG_H

#include <stdio.h>
#define qDebug(...) fprintf(stderr, __VA_ARGS__)
#define qWarning printf
#define qFatal printf
inline void qt_noop(void) {}
#define Q_ASSERT(cond)                                            \
    if (!(cond))                                                  \
        printf("ASSERT in file %s, line %d", __FILE__, __LINE__); \
    else                                                          \
        qt_noop()

#endif
