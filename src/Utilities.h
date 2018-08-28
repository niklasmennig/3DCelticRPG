#pragma once

namespace Utilities {
    float Clamp(float value, float min, float max) {
        float res = value;
        if (res < min)
            res = min;
        if (res > max)
            res = max;
        return res;
    }
}