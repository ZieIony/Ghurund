#pragma once

#include "Drawable.h"

namespace Ghurund::UI {
    class ImageDrawable:public Drawable {
    private:
        uint32_t tint = 0;
        float alpha = 1.0f;

    public:
        virtual ~ImageDrawable()
        //    = 0   // TODO: a destructor cannot be abstract
        {}

        inline void setTint(const uint32_t color) {
            this->tint = color;
        }

        inline uint32_t getTint() const {
            return tint;
        }

        __declspec(property(get = getTint, put = setTint)) uint32_t Tint;

        inline void setAlpha(const float alpha) {
            this->alpha = alpha;
        }

        inline float getAlpha() const {
            return alpha;
        }

        __declspec(property(get = getAlpha, put = setAlpha)) float Alpha;
    };
}