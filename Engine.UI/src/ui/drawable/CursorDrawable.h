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
            preferredSize.width = PreferredSize::Width(width);
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        inline const Color& getColor() const {
            return this->color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void update(const uint64_t time) override {
            visible = fmod(time, blinkTimeMs) < blinkTimeMs / 2.0f;
        }

        virtual void onDraw(Canvas& canvas) override {
            if (visible)
                canvas.fillRect(0, 0, size.width, size.height, color);
            owner->repaint();
        }
    };
}