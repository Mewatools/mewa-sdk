/***************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#include "mxmodule.h"

MxModule::MxModule()
{
}

/**
 * \class MxModule
 * \brief Interface class for modules to handle rendering and user mouse/touch events.
 *
 * An MxModule renders an image based on inputs provided via an \c MxCompositor
 * and can expose controls via an \c MxControlPanel. This class defines the
 * interface that plugin modules should implement to participate in rendering
 * and interaction.
 *
 * The documentation for the class and its members is placed here in the
 * implementation file so you can keep comments next to the implementation
 * files while keeping the header clean. Doxygen will associate the
 * descriptions below with the declarations in the header because we use the
 * \class and \fn tags with fully qualified names.
 *
 * See the plugin example: https://github.com/Mewatools/mewa-sdk/tree/main/examples/simpletriangle
 *
 * \sa MxCompositor, MxControlPanel
 */

/**
 * \fn void MxModule::onMousePress(int x, int y, unsigned int button)
 * \brief Handles mouse press events.
 * \param x The x-coordinate of the mouse press.
 * \param y The y-coordinate of the mouse press.
 * \param button The mouse button that was pressed.
 *
 * Override this method to implement custom mouse press handling for
 * interactive modules embedded in a webpage-like environment.
 */

/**
 * \fn void MxModule::onMouseMove(int x, int y)
 * \brief Handles mouse move events.
 * \param x The x-coordinate of the mouse cursor.
 * \param y The y-coordinate of the mouse cursor.
 *
 * Override to implement custom mouse move handling.
 */

/**
 * \fn void MxModule::onMouseRelease(int x, int y)
 * \brief Handles mouse release events.
 * \param x The x-coordinate of the mouse release.
 * \param y The y-coordinate of the mouse release.
 *
 * Override to implement custom mouse release handling.
 */

/**
 * \fn void MxModule::renderOutput(MxCompositor &compositor)
 * \brief Renders the module's output.
 * \param compositor Provides input data and rendering context for the module.
 *
 * This pure virtual function must be implemented by subclasses. It is
 * responsible for generating the visual output of the module using the
 * provided compositor.
 */

/**
 * \fn void MxModule::setupControlPanel(MxControlPanel *panel)
 * \brief Sets up the control panel for the module.
 * \param panel Pointer to the control panel to configure.
 *
 * Override this method to add controls for video/template usage.
 */
