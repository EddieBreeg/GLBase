#pragma once

#include "Texture.hpp"

namespace GLBase
{
    // Represents an OpenGL framebuffer object
    class FrameBuffer
    {
    private:
        unsigned _id = 0;
        constexpr FrameBuffer(nullptr_t);
    public:
        FrameBuffer();
        void bind() const;
        void unbind() const;
        void attachTexture2D(const Texture& tex, unsigned attachmentIndex);
        // Returns the current status of the framebuffer, as returned by glCheckFramebufferStatus
        unsigned status() const;
        // Returns a null terminated human readable string describing the current status
        static const char *statusString(unsigned status);
        ~FrameBuffer();
    };
    
} // namespace GLBase
