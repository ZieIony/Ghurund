#pragma once

namespace Ghurund::UI {
    /*class CursorDrawable: public Drawable {
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

        virtual void update(uint64_t time) override {
            visible = fmod(time, blinkTimeMs) < blinkTimeMs / 2.0f;
        }

        virtual void draw(RenderGroup& group, const Ghurund::Core::FloatSize& size, const Ghurund::UI::Color& tint) const override;
    };*/
}