#pragma once

#include "Vector.hpp"
#include <utility>

namespace GLBase
{
    inline Vector3 rgb2hsv(const Vector3& rgb)
    {
        float M = std::max(rgb.r, std::max(rgb.g, rgb.b));
        float m = std::min(rgb.r, std::min(rgb.g, rgb.b));
        float C = M - m;
        float h;
        if(rgb.r == M)
            h = (rgb.g - rgb.b) / C + 6 * (rgb.g < rgb.b);
        else if(rgb.g == M)
            h = (rgb.b - rgb.r) / C + 2;
        else 
            h = (rgb.r - rgb.g) / C + 4;
        h /= 6;
        float s = M? C/M : 0;
        return {h, s, M};
    }
    inline Vector3 hsv2rgb(const Vector3& hsv)
    {
        int i = int(hsv.x * 6) % 6;
        float f = hsv.x * 6 - i;
        float p = hsv.z * (1 - hsv.y);
        float q = hsv.z * (1 - f * hsv.y);
        float t = hsv.z * (1 - (1 - f) * hsv.y);
        switch (i % 6)
        {
        case 0: return {hsv.x, t, p};
        case 1: return {q, hsv.z, p};
        case 2: return {p, hsv.z, t};
        case 3: return {p, q, hsv.z};
        case 4: return {t, p, hsv.z};
        case 5: return {hsv.x, p, q};
        }
    }
} // namespace GLBase
