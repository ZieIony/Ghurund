#include "ghuipch.h"
#include "ScrollView.h"
#include "core/reflection/TypeBuilder.h"

#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ScrollView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ScrollView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ScrollView>(NAMESPACE_NAME, GH_STRINGIFY(ScrollView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ScrollView::onDraw(ICanvas& canvas) {
        canvas.save();
        canvas.clipRect(0, 0, Size.Width, Size.Height);
        canvas.translate(-scroll.x, -scroll.y);
        __super::onDraw(canvas);
        canvas.restoreClipRect();
        canvas.restore();
    }
    
    void ScrollView::onLayout(float x, float y, float width, float height) {
        if (Child) {
            Child->layout(0, 0,
                Child->PreferredSize.width == PreferredSize::Width::FILL ? width : Child->MeasuredSize.Width,
                Child->PreferredSize.height == PreferredSize::Height::FILL ? height : Child->MeasuredSize.Height);
            maxScroll = {
                std::max(0.0f, Child->Size.Width - Size.Width),
                std::max(0.0f, Child->Size.Height - Size.Height)
            };
            scroll = {
                std::max(0.0f, std::min(scroll.x, maxScroll.x)),
                std::max(0.0f, std::min(scroll.y, maxScroll.y))
            };
        }
    }
    
    bool ScrollView::dispatchKeyEvent(const KeyEventArgs& event) {
        if (event.Action == Ghurund::Core::KeyAction::DOWN && event.Key == VK_NEXT) {
            FloatPoint prevScroll = scroll;
            if (Child && Child->Size.Height == Size.Height) {
                Scroll = { Scroll.x + Size.Width, Scroll.y };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
            } else {
                Scroll = { Scroll.x , Scroll.y + Size.Height };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.Key == VK_PRIOR) {
            FloatPoint prevScroll = scroll;
            if (Child && Child->Size.Height == Size.Height) {
                Scroll = { Scroll.x - Size.Width, Scroll.y };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
            } else {
                Scroll = { Scroll.x, Scroll.y - Size.Height };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.Key == VK_HOME) {
            FloatPoint prevScroll = scroll;
            Scroll = { 0.0f,0.0f };
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                OnScrolled();
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.Key == VK_END) {
            FloatPoint prevScroll = scroll;
            Scroll = MaxScroll;
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                OnScrolled();
            }
            return true;
        }
        return __super::dispatchKeyEvent(event);
    }
    
    bool ScrollView::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (Child) {
            FloatPoint prevScroll = scroll;
            if (event.Wheel == MouseWheel::HORIZONTAL || Child->Size.Height == Size.Height) {
                scroll.x = std::max(0.0f, std::min(scroll.x - event.Delta, maxScroll.x));
            } else if (event.Wheel == MouseWheel::VERTICAL) {
                scroll.y = std::max(0.0f, std::min(scroll.y - event.Delta, maxScroll.y));
            }
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                OnScrolled();
            }
        }
        return mouseWheelEvent(event);
    }
}
