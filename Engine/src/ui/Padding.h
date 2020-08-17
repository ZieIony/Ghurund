#pragma once

namespace Ghurund::UI {
    class Padding {
    public:
        float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;

        inline void setAll(float value) {
            left = top = right = bottom = value;
        }

        __declspec(property(put = setAll)) float All;

        inline void setVertical(float value) {
            top = bottom = value;
        }

        __declspec(property(put = setVertical)) float Vertical;

        inline void setHorizontal(float value) {
            left = right = value;
        }

        __declspec(property(put = setHorizontal)) float Horizontal;
    };
}