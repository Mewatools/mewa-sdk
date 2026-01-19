/****************************************************************************
** Copyright (C) 2020-2026 Mewatools <hugo@mewatools.com>
** SPDX-License-Identifier: MIT License
****************************************************************************/
#ifndef MXTEXTURE_H
#define MXTEXTURE_H

#include "mxvector.h"
#include "mxopengl.h"

class MxRenderer;

/*! MxTexture abstracts a Gpu texture.

 \sa MxRenderer
*/
class MxTexture
{
public:
    /** @brief Texture pixel format
     *
     *  Defines the format of pixel data stored in the texture
     */
    enum PixelFormat
    {
        Uninitialized = 0, //!< Uninitialized texture format
        RGBA8,             //!< 8 bit per pixel, RGBA
        RGBAFloat,         //!< Floating point RGBA format
    };

    // texture parameters
    enum FilterParameter
    {
        NoFilter = 0x1, // default (nearest filter)
        LinearFilter = 0x02,
        // MipmapFilter = 0x04,
        MipmapLinearFilter = 0x08,

        FilterMask = 0xF // reserved for BINARY-AND with filter options
    };

    enum WrapParameter
    {
        ClampWrap = 0x10,
        RepeatWrap = 0x20,

        WrapMask = 0x30 // reserved for BINARY-AND
    };

    MxTexture();
    virtual ~MxTexture();

    /** Creates a texture with the given parameters
     *
     *  @param renderer The renderer to use for texture creation
     *  @param size The size of the texture (must be power of two)
     *  @param format The pixel format of the texture
     *  @param bits The pixel data to initialize the texture with
     */
    void create(MxRenderer *renderer, const MxVector2I &size, PixelFormat format, const void *bits);

    void discardGLResources();
    bool isNull() const;

    /** Sets the given pixel data to this texture
     *
     *  @param renderer The renderer to use for texture updates
     *  @param pixels The pixel data to set
     *  @param size The size of the pixel data
     *  @param format The pixel format of the data
     */
    void setData(MxRenderer *renderer, const unsigned char *pixels, const MxVector2I &size, MxTexture::PixelFormat format);

    // Parameters are the bits defined in FilterParameter and WrapParameter. Its safe to call before every draw
    void setParameters(MxRenderer *renderer, unsigned char newParameters);

public:
    void setGLInterpolation(MxRenderer *renderer, int filter);
    void setGLWrap(MxRenderer *renderer, int wrap);
    void updateMipmaps(MxRenderer *renderer); // call it everytime the texture content changes
    GLenum glFormat(PixelFormat format);      // format can be RGB, RGBA, and A.
    GLenum glType(PixelFormat format);

    int mWidth;
    int mHeight;
    int mTextureWidth;
    int mTextureHeight;
    int mChannels;
    GLuint mTextureId;
    unsigned char pCurrParameters;
};

#endif
