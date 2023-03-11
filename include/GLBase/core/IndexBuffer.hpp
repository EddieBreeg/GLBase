#pragma once
#include <inttypes.h>
#include "GLBuffer.hpp"

namespace GLBase
{
    // Represents an OpenGL index buffer object
    class IndexBuffer: public GLBuffer
    {
    private:
        unsigned _count;
    public:
        /* Constructs the index buffer object
        @param data: a pointer to the indices. If null, the buffer will still be allocated on the GPU
        @param count: the number of indices in the buffer
        @param usage: hint as to how the buffer will be used. Valid values are: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
        */
        IndexBuffer(const uint32_t *data, unsigned count, unsigned usage);
        /* Sets the data of the buffer
        @param data: a pointer to the indices. If null, the buffer will still be allocated on the GPU
        @param count: the number of indices in the buffer
        @param usage: hint as to how the buffer will be used. Valid values are: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
        */
        void setIndexData(const uint32_t *data, unsigned count, unsigned usage);
        // Returns the number of indices in the buffer
        unsigned count() const;
        ~IndexBuffer();
    };
    
} // namespace GLBase
