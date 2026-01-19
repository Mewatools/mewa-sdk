/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXBUFFER_H
#define MXBUFFER_H

class MxBuffer
{
public:
    MxBuffer();
    ~MxBuffer();
    MxBuffer &operator=(const MxBuffer &other);

    void reserveForAppend(int size);
    char *alloc(int size, int growBy);
    void clear();
    void append(const char *data, int size);
    char *reserveAndGet(int size);
    int size() const;
    void addToSize(int amount);
    const char *data() const;
    char *end();

    char *pData;
    int pSize;
    int pAlloc;
};

#endif
