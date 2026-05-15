/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/

// gcc -o test main.cpp -lGL -lX11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "appabstraction.h"
#include MX_MODULE_HEADER

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
// Additional attributes for core profile contexts
#ifndef GLX_CONTEXT_PROFILE_MASK_ARB
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
#endif
#ifndef GLX_CONTEXT_CORE_PROFILE_BIT_ARB
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#endif
#ifndef GLX_CONTEXT_FLAGS_ARB
#define GLX_CONTEXT_FLAGS_ARB 0x2094
#endif
#ifndef GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#endif
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);

// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension)
{
    const char *start;
    const char *where, *terminator;

    /* Extension names should not have spaces. */
    where = strchr(extension, ' ');
    if (where || *extension == '\0')
        return false;

    /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */
    for (start = extList;;)
    {
        where = strstr(start, extension);

        if (!where)
            break;

        terminator = where + strlen(extension);

        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return true;

        start = terminator;
    }

    return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
{
    ctxErrorOccurred = true;
    return 0;
}

int main(int argc, char *argv[])
{

    Display *display = XOpenDisplay(NULL);

    if (!display)
    {
        printf("Failed to open X display\n");
        exit(1);
    }

    // Get a matching FB config
    static int visual_attribs[] =
        {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            //  GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            // GLX_SAMPLE_BUFFERS  , 1,
            // GLX_SAMPLES         , 4,
            None};

    int glx_major, glx_minor;

    // FBConfigs were added in GLX version 1.3.
    if (!glXQueryVersion(display, &glx_major, &glx_minor) ||
        ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
    {
        printf("Invalid GLX version");
        exit(1);
    }

    printf("Getting matching framebuffer configs\n");
    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fbcount);
    if (!fbc)
    {
        printf("Failed to retrieve a framebuffer config\n");
        exit(1);
    }
    printf("Found %d matching FB configs.\n", fbcount);

    // Pick the FB config/visual with the most samples per pixel
    printf("Getting XVisualInfos\n");
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    int i;
    for (i = 0; i < fbcount; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i]);
        if (vi)
        {
            int samp_buf, samples;
            glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

            printf("  Matching fbconfig %d, SAMPLE_BUFFERS = %d,"
                   " SAMPLES = %d\n",
                   i, samp_buf, samples);

            if (best_fbc < 0 || samp_buf && samples > best_num_samp)
                best_fbc = i, best_num_samp = samples;
            if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                worst_fbc = i, worst_num_samp = samples;
        }
        XFree(vi);
    }

    GLXFBConfig bestFbc = fbc[best_fbc];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree(fbc);

    // Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc);
    printf("Chosen visual ID = 0x%lx\n", vi->visualid);

    printf("Creating colormap\n");
    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap(display,
                                          RootWindow(display, vi->screen),
                                          vi->visual, AllocNone);
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask | ExposureMask | ButtonPressMask | PointerMotionMask;

    int windowWidth = 800;
    int windowHeight = 600;

    printf("Creating window\n");
    Window win = XCreateWindow(display, RootWindow(display, vi->screen),
                               0, 0, windowWidth, windowHeight, 0, vi->depth, InputOutput,
                               vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &swa);
    if (!win)
    {
        printf("Failed to create window.\n");
        exit(1);
    }

    // Done with the visual info data
    XFree(vi);

    XStoreName(display, win, "Mewa Console");

    printf("Mapping window\n");
    XMapWindow(display, win);

    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString(display,
                                                   DefaultScreen(display));

    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

    GLXContext ctx = 0;

    // Install an X error handler so the application won't exit if GL 3.0
    // context allocation fails.
    //
    // Note this error handler is global.  All display connections in all threads
    // of a process use the same error handler, so be sure to guard against other
    // threads issuing X commands while this code is running.
    ctxErrorOccurred = false;
    int (*oldHandler)(Display *, XErrorEvent *) =
        XSetErrorHandler(&ctxErrorHandler);

    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB)
    {
        printf("glXCreateContextAttribsARB() not found"
               " ... using old-style GLX context\n");
        ctx = glXCreateNewContext(display, bestFbc, GLX_RGBA_TYPE, 0, True);
    }

    // If it does, try to get a GL 3.0 context!
    else
    {
        int context_attribs[] =
            {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 3,
                GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                // GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                None};

        printf("Creating context\n");
        ctx = glXCreateContextAttribsARB(display, bestFbc, 0,
                                         True, context_attribs);

        // Sync to ensure any errors generated are processed.
        XSync(display, False);
        if (!ctxErrorOccurred && ctx)
            printf("Created GL 3.3 core context\n");
        else
        {
            // Couldn't create GL 3.3 core context.  Fall back to old-style 2.x context.
            // When a context version below 3.0 is requested, implementations will
            // return the newest context version compatible with OpenGL versions less
            // than version 3.0.
            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

            printf("Failed to create GL 3.3 context"
                   " ... using old-style GLX context\n");
            ctx = glXCreateContextAttribsARB(display, bestFbc, 0,
                                             True, context_attribs);
        }
    }

    // Sync to ensure any errors generated are processed.
    XSync(display, False);

    // Restore the original error handler
    XSetErrorHandler(oldHandler);

    if (ctxErrorOccurred || !ctx)
    {
        printf("Failed to create an OpenGL context\n");
        exit(1);
    }

    // Verifying that context is a direct context
    if (!glXIsDirect(display, ctx))
    {
        printf("Indirect GLX rendering context obtained\n");
    }
    else
    {
        printf("Direct GLX rendering context obtained\n");
    }

    printf("Making context current\n");
    glXMakeCurrent(display, win, ctx);

    AppAbstraction *app = new AppAbstraction();
    app->setModule(new MX_MODULE_CLASS());
    app->setupGL(windowWidth, windowHeight);

    // time in secs
    float t = 0.0f;
    int state = 0;

    // Get initial time
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    double lastTime = now.tv_sec + now.tv_nsec / 1000000000.0;

    do
    {
        // Handle X11 events
        while (XPending(display))
        {
            XEvent event;
            XNextEvent(display, &event);

            if (event.type == ConfigureNotify)
            {
                XConfigureEvent *ce = &event.xconfigure;
                if (ce->width != windowWidth || ce->height != windowHeight)
                {
                    windowWidth = ce->width;
                    windowHeight = ce->height;
                    printf("Window resized to %dx%d\n", windowWidth, windowHeight);
                    app->onResize(windowWidth, windowHeight);
                }
            }
            else if (event.type == ButtonPress)
            {
                XButtonEvent *be = &event.xbutton;
                MxVector2F mousePos(static_cast<float>(be->x), static_cast<float>(be->y));
                app->onMousePress(mousePos);
            }
            else if (event.type == MotionNotify)
            {
                XMotionEvent *me = &event.xmotion;
                MxVector2F mousePos(static_cast<float>(me->x), static_cast<float>(me->y));
                app->onMouseMove(mousePos);
            }
        }

        // Get current time and calculate delta
        clock_gettime(CLOCK_MONOTONIC, &now);
        double currentTime = now.tv_sec + now.tv_nsec / 1000000000.0;
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        app->render(t);
        t += deltaTime;

        glXSwapBuffers(display, win);

    } while (1);

    glXMakeCurrent(display, 0, 0);
    glXDestroyContext(display, ctx);

    XDestroyWindow(display, win);
    XFreeColormap(display, cmap);
    XCloseDisplay(display);

    return 0;
}
