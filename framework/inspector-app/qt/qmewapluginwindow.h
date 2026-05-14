/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef QMEWAPLUGINWINDOW_H
#define QMEWAPLUGINWINDOW_H

#include <QOpenGLWindow>
#include <QElapsedTimer>

#include "appabstraction.h"

class MxModule;

class QMewaPluginWindow : public QOpenGLWindow
{

public:
    QMewaPluginWindow();
    virtual ~QMewaPluginWindow();

    void setPlugin(MxModule *plugin);

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    /* MxInputs pInputs;
     MxModule *pPlugin;
     MxGuiRenderer pRenderer;*/
    AppAbstraction pApp;

    bool pFirstTime;
    QElapsedTimer pTimer;
};

#endif
