#pragma once

namespace Ghurund::Core {
    struct FloatRect {
        float left, top, right, bottom;

        inline float getWidth() const {
            return right - left;
        }

        __declspec(property(get = getWidth)) float Width;

        inline float getHeight() const {
            return bottom - top;
        }

        __declspec(property(get = getHeight)) float Height;
    };
}