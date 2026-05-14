/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include <QMouseEvent>

#include "qmewapluginwindow.h"
// #include "mxmodule.h"

QMewaPluginWindow::QMewaPluginWindow()
    : QOpenGLWindow(QOpenGLWindow::PartialUpdateBlit)
{
    // pPlugin = nullptr;
    pFirstTime = true;
}

QMewaPluginWindow::~QMewaPluginWindow()
{
}

void QMewaPluginWindow::setPlugin(MxModule *plugin)
{
    pApp.pNode = plugin;
}

void QMewaPluginWindow::initializeGL()
{
    pApp.pCompositor.pRenderer.initializeOpenGLFunctions();

    pTimer.start();
}

void QMewaPluginWindow::resizeGL(int w, int h)
{
    pApp.pCompositor.pRenderer.setWindowSize(w, h);
}

void QMewaPluginWindow::paintGL()
{
    if (pFirstTime)
    { // for unknown reason initializeGL() looses bounded textures, so load textures here!
        pFirstTime = false;

        pApp.pCompositor.pRenderer.initialize();
        pApp.pCompositor.pRenderer.glClearColor(102.0f / 255.0f, 102.0f / 255.0f, 102.0f / 255.0f, 1.0f);
        pApp.pCompositor.pRenderer.enableDepthTest(false);
    }

    pApp.pCompositor.pRenderer.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    const MxVector2I &screen = pApp.pCompositor.pRenderer.windowSize();
    pApp.pCompositor.pRenderer.setViewport(0, 0, screen.width(), screen.height());

    pApp.pCompositor.pOutputResolution = screen;
    pApp.pCompositor.pTime += (1.0f / 60.f); // 60 fps
    pApp.pNode->renderOutput(pApp.pCompositor);

    pApp.pCompositor.pRenderer.checkGLError(__FILE__, __LINE__);

    update();
}

void QMewaPluginWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
}

void QMewaPluginWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
}

void QMewaPluginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
}
