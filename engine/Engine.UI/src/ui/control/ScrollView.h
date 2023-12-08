#pragma once

#include "ControlContainer.h"

#include <algorithm>

namespace Ghurund::UI {
    class ScrollView:public ControlContainer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ScrollView::GET_TYPE();
#pragma endregion

    private:
        FloatPoint scroll = { 0.0f, 0.0f };
        FloatPoint maxScroll = { 0.0f, 0.0f };

    protected:
        virtual void onDraw(ICanvas& canvas) override;

        virtual void onLayout(float x, float y, float width, float height) override;

    public:
        Event<Control> onScrolled = *this;

        inline const FloatPoint& getScroll() const {
            return scroll;
        }

        inline void setScroll(const FloatPoint& scroll) {
            setScroll(scroll.x, scroll.y);
        }

        inline void setScroll(float x, float y) {
            if (Child) {
                scroll = {
                    std::max(0.0f, std::min(x, maxScroll.x)),
                    std::max(0.0f, std::min(y, maxScroll.y))
                };
            } else {
                this->scroll = { 0.0f, 0.0f };
            }
        }

        __declspec(property(get = getScroll, put = setScroll)) const FloatPoint& Scroll;

        inline const FloatPoint& getMaxScroll() const {
            return maxScroll;
        }

        __declspec(property(get = getMaxScroll)) const FloatPoint& MaxScroll;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return __super::dispatchMouseButtonEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event);
    };
}