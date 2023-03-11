#pragma once

#include <inttypes.h>
#include <utility>

#ifndef  __glew_h__
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_RGB 0x1907
#endif

namespace GLBase
{
    // Interface for an OpenGL texture object
    class Texture
    {
    private:
        unsigned _id;
        unsigned _w, _h;
        unsigned _format;
        unsigned _type;
        unsigned _wrapMode = GL_CLAMP_TO_BORDER;
    public:
        struct RGBAPixel
        {
            uint8_t r, g, b, a;
        };
        
        /* Constructs the texture
        @param width: the width of the texture, in pixels
        @param height: the height of the texture, in pixels
        @param format: Format of the pixel data. Valid values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
        @param wrapMode: Specifies how to wrap the texture. Valid values are GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
         */
        Texture(unsigned width, unsigned height, unsigned format, unsigned wrapMode = GL_CLAMP_TO_BORDER);
        /* Constructs the texture
        @param width: the width of the texture, in pixels
        @param height: the height of the texture, in pixels
        @param format: Format of the pixel data. Valid values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
        @param type: The datatype used in the pixel data. Valid values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV
        @param data: A pointer to the pixel data. The first pixel corresponds to the top left hand corner in the image. If null, the buffer will still be allocated on the GPU to hold the texture, but the memory will be uninitialized
        @param wrapMode: Specifies how to wrap the texture. Valid values are GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
         */
        Texture(unsigned width, unsigned height, unsigned format, unsigned type, const void* data,
            unsigned wrapMode = GL_CLAMP_TO_BORDER);
        Texture();
        std::pair<unsigned, unsigned> getSize() const;
        /* Sets the wrap mode for texture 
        @param mode: Either GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT or GL_REPEAT
        */
        void setWrapMode(unsigned mode);
        /* Sets the filter mode for texture 
        @param mode: Either GL_NEAREST or GL_LINEAR
        */
        void setFilterMode(unsigned mode);
        /* Resizes the texture
        @param w: the new width in pixels
        @param h: the new height in pixels
        @param format: the pixel format. Valid values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
         */
        void resize(unsigned w, unsigned h, unsigned format=GL_RGB);
        /* Writes the texture data
        @param width: the width of the texture, in pixels
        @param height: the height of the texture, in pixels
        @param format: Format of the pixel data. Valid values are GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
        @param type: The datatype used in the pixel data. Valid values are GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV
        @param data: A pointer to the pixel data. The first pixel corresponds to the top left hand corner in the image.
        */
        void writeData(unsigned width, unsigned height, unsigned format, unsigned type, const void* data);
        void bind() const;
        /* Sets the currently active texture unit, and then binds the texture
        @param unit: The index of the unit to use
        */
        void bind(unsigned unit) const;
        void unbind() const;
        unsigned getID() const { return _id; }
        ~Texture();
    };
} // namespace GLBase

#ifndef __glew_h__
#undef GL_CLAMP_TO_BORDER
#undef GL_RGB
#endif

