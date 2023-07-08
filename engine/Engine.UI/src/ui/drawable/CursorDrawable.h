#pragma once

#include "Drawable.h"
#include "core/Timer.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    class CursorDrawable: public Drawable {
    private:
        Color color;
        uint64_t blinkTimeMs;
        bool visible = true;

    public:
        CursorDrawable(const Color& color = 0x7f000000, float width = 2.0f, uint64_t blinkTimeMs = 1000):blinkTimeMs(blinkTimeMs), color(color) {
            preferredSize.Width = width;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(put = setColor)) const Color& Color;

        virtual void update(const uint64_t time) override {
            visible = fmod(time, blinkTimeMs) < blinkTimeMs / 2.0f;
        }

        virtual void onDraw(ICanvas& canvas, const Ghurund::Core::FloatSize& size) const override;
    };
}