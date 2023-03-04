#pragma once

#include "Texture.hpp"

namespace GLBase
{
    class FrameBuffer
    {
    private:
        unsigned _id = 0;
        constexpr FrameBuffer(nullptr_t);
    public:
        FrameBuffer();
        static FrameBuffer& defaultFrameBuffer();
        void bind() const;
        void unbind() const;
        void attachTexture2D(const Texture& tex, unsigned attachmentIndex);
        unsigned status() const;
        static const char *statusString(unsigned status);
        ~FrameBuffer();
    };
    
} // namespace GLBase
