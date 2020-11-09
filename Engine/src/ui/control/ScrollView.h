#pragma once

#include "ControlContainer.h"

#include <algorithm>

namespace Ghurund::UI {
    class ScrollView:public ControlContainer {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ScrollView))
                .withConstructor(NoArgsConstructor<ScrollView>())
                .withSupertype(__super::TYPE);

            return TYPE;
        }

        XMFLOAT2 scroll = { 0.0f, 0.0f };
        Event<Control> onScrolled = Event<Control>(*this);

    public:
        inline const XMFLOAT2& getScroll() const {
            return scroll;
        }

        inline void setScroll(const XMFLOAT2& scroll) {
            setScroll(scroll.x, scroll.y);
        }

        inline void setScroll(float x, float y) {
            if (Child) {
                this->scroll.x = std::max(-Child->Size.width, std::min(x, 0.0f));
                this->scroll.y = std::max(-Child->Size.height, std::min(y, 0.0f));
            } else {
                this->scroll = { 0.0f, 0.0f };
            }
        }

        __declspec(property(get = getScroll, put = setScroll)) const XMFLOAT2& Scroll;

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

        virtual void onDraw(Canvas& canvas) override {
            canvas.save();
            canvas.clipRect(0, 0, Size.width, Size.height);
            canvas.translate(scroll.x, scroll.y);
            __super::onDraw(canvas);
            canvas.restore();
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (Child)
                Child->layout(0, 0,
                    Child->PreferredSize.width == PreferredSize::Width::FILL ? width : Child->MeasuredSize.width,
                    Child->PreferredSize.height == PreferredSize::Height::FILL ? height : Child->MeasuredSize.height);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return __super::dispatchMouseButtonEvent(event.translate(-scroll.x, -scroll.y));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event.translate(-scroll.x, -scroll.y));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            if (Child) {
                XMFLOAT2 prevScroll = scroll;
                if (event.Wheel == MouseWheel::HORIZONTAL || Child->Size.height == Size.height) {
                    scroll.x = std::max(Size.width - Child->Size.width, std::min(scroll.x + event.Delta, 0.0f));
                } else if (event.Wheel == MouseWheel::VERTICAL) {
                    scroll.y = std::max(Size.height - Child->Size.height, std::min(scroll.y + event.Delta, 0.0f));
                }
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
            }
            return OnMouseWheel(event);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ScrollView> ScrollViewPtr;
}