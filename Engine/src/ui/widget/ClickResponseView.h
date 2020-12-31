#pragma once

#include "ui/control/ClickableView.h"

#include <ctime>

namespace Ghurund::UI {
    class ClickResponseView:public Control {
    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        Paint paint;
        bool finishedAnimating = true, pressed = false;
        uint32_t color;

    public:
        ClickResponseView(uint32_t color = 0x3fffffff) {
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            this->color = color;
        }

        inline uint32_t getColor() const {
            return color;
        }

        inline void setColor(uint32_t color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) uint32_t Color;

        inline bool isPressed() const {
            return pressed;
        }

        inline void setPressed(bool pressed) {
            this->pressed = pressed;
        }

        __declspec(property(get = isPressed, put = setPressed)) bool Pressed;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onDraw(Canvas& canvas) override {
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
            if (!finishedAnimating)
                repaint();
        }
    };
}