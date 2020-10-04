#pragma once

#include "ControlContainer.h"

namespace Ghurund::UI {
    class ScrollView:public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ScrollView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ScrollView>();

        XMFLOAT2 scroll = { 0.0f, 0.0f };

    public:
        virtual void onDraw(Canvas& canvas) override {
            canvas.save();
            canvas.clipRect(0, 0, size.width, size.height);
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
                if (event.Wheel == MouseWheel::HORIZONTAL) {
                    scroll.x = std::max(Size.width - Child->Size.width, std::min(scroll.x + event.Delta, 0.0f));
                } else if (event.Wheel == MouseWheel::VERTICAL) {
                    scroll.y = std::max(Size.height - Child->Size.height, std::min(scroll.y + event.Delta, 0.0f));
                }
                repaint();
            }
            return OnMouseWheel(event);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ScrollView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ScrollView> ScrollViewPtr;
}