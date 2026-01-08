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
        XMFLOAT2 scroll = { 0.0f, 0.0f };
        XMFLOAT2 maxScroll = { 0.0f, 0.0f };

    protected:
        virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual bool onKeyEvent(const KeyEventArgs& event) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return __super::dispatchMouseButtonEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
            return __super::dispatchMouseMotionEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event);

    public:
        Event<Control> onScrolled = *this;

        inline const XMFLOAT2& getScroll() const {
            return scroll;
        }

        inline void setScroll(const XMFLOAT2& scroll) {
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

        __declspec(property(get = getScroll, put = setScroll)) const XMFLOAT2& Scroll;

        inline const XMFLOAT2& getMaxScroll() const {
            return maxScroll;
        }

        __declspec(property(get = getMaxScroll)) const XMFLOAT2& MaxScroll;
    };
}