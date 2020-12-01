#pragma once

#include "DragHelper.h"
#include "VerticalScrollBarLayout.h"
#include "Widget.h"

#include <algorithm>

namespace Ghurund::UI {
    class VerticalScrollBar:public Widget<VerticalScrollBarLayout> {
    private:
        uint32_t pressMousePos = 0;
        float pressBarPos = 0;
        DragHelper dragHelper;

        float scroll = 0;
        float maxScroll = 100;
        Event<Control> onScrolled = Event<Control>(*this);

        void updateBar();

        void updateScroll();

    public:
        VerticalScrollBar(VerticalScrollBarLayout* layout);

        VerticalScrollBar(Ghurund::UI::Theme& theme):VerticalScrollBar(ghnew VerticalScrollBarLayout(theme)) {}

        inline float getScroll() const {
            return scroll;
        }

        inline void setScroll(float scroll) {
            this->scroll = std::max(0.0f, std::min(scroll, maxScroll));
            updateBar();
        }

        __declspec(property(get = getScroll, put = setScroll)) float Scroll;

        inline float getMaxScroll() const {
            return maxScroll;
        }

        inline void setMaxScroll(float maxScroll) {
            this->maxScroll = std::max(0.0f, maxScroll);
            Scroll = std::max(0.0f, std::min(scroll, maxScroll));
        }

        __declspec(property(get = getMaxScroll, put = setMaxScroll)) float MaxScroll;

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            __super::onMeasure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
        }
    };

    typedef SharedPointer<VerticalScrollBar> VerticalScrollBarPtr;
}