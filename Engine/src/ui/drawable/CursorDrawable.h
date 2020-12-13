#pragma once

#include "Drawable.h"
#include "ui/Canvas.h"
#include "application/Timer.h"

namespace Ghurund::UI {
    class CursorDrawable:public Drawable {
    private:
        Paint paint;
        float blinkTime;
        bool visible = true;

    public:
        CursorDrawable(uint32_t color = 0x7f000000, float width = 2.0f, float blinkTime = 2.0f):blinkTime(blinkTime) {
            Color = color;
            preferredSize.width = PreferredSize::Width(width);
        }

        inline void setColor(uint32_t color) {
            paint.Color = color;
        }

        inline uint32_t getColor() const {
            return paint.Color;
        }

        __declspec(property(get = getColor, put = setColor)) uint32_t Color;

        virtual void update(const Timer& timer) override {
            visible = fmod(timer.Time, blinkTime) < blinkTime / 2;
        }

        virtual void onDraw(Canvas& canvas) override {
            if (visible)
                canvas.fillRect(0, 0, size.width, size.height, paint);
            owner->repaint();
        }
    };
}