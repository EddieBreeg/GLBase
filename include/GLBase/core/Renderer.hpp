#pragma once

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

namespace GLBase
{
    // API for a very simple renderer
    class Renderer
    {
    public:
        /* Issues a draw call to the GPU
        @param vArray: The vertex array linked to the vertex buffer and vertex layout to use
        @param iBuffer: The indices to use to render the triangles
        @param shader: What shader to use to render the object
        */
        void draw(const VertexArray& vArray, const IndexBuffer& iBuffer, const Shader& shader) const;
        // Clears the color buffer
        void clear() const;
        // Selects the clear color to use, in RGBA format. The values should be normalized between 0 and 1
        void setClearColor(float r, float g, float b, float a=1.0f) const;
    };
    
} // namespace GLBase
