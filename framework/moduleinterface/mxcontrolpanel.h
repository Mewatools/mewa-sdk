/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXCONTROLPANEL_H
#define MXCONTROLPANEL_H

class MxFloatControl;

class MxControlPanel
{
public:
    MxControlPanel();

    /*!
     * \brief MxParameter holds the input parameter value
     * \param value Default parameter value
     * \param transitionTime Default transition time

    Returns the UI control where the range and step should be set.
    */
    MxFloatControl *addFloatControl(const char *name, float value, float transitionTime);
};

#endif // MXCONTROLPANEL_H
