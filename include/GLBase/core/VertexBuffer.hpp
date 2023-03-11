#pragma once
#include "GLBuffer.hpp"


namespace GLBase
{
    // The interface for an OpenGL vertex buffer object
    class VertexBuffer: public GLBuffer
    {
    public:
        /* Constructs the buffer
        @param data: a pointer to the data. If null, the memory will still be allocated on the GPU
        @param size: the total size of the buffer, in bytes
        @param usage: hint as to how the buffer will be used. Valid values are: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
        */
        VertexBuffer(const void *data, unsigned size, unsigned usage);
         /* Sets the data of the buffer
        @param data: a pointer to the vertex data. If null, the buffer will still be allocated on the GPU
        @param size: the total size of the buffer, in bytes
        @param usage: hint as to how the buffer will be used. Valid values are: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
        */
        void setVertexData(const void *data, unsigned size, unsigned usage);
        ~VertexBuffer();
    };
} // namespace GLBase
