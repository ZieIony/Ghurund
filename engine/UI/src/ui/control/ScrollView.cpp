#include "ghuipch.h"
#include "ScrollView.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ScrollView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ScrollView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ScrollView>()
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ScrollView::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
        //canvas.save();
        //canvas.clipRect(0, 0, Size.Width, Size.Height);
        //canvas.translate(-scroll.x, -scroll.y);
        __super::onDraw(group, parentPosition);
        //canvas.restoreClipRect();
        //canvas.restore();
    }
    
    void ScrollView::onLayout(float x, float y, float width, float height) {
        if (Child) {
            Child->layout(0, 0, width, height);
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
    
    bool ScrollView::onKeyEvent(const KeyEventArgs& event) {
        if (event.Action == Ghurund::Core::KeyAction::DOWN && event.KeyCode == VK_NEXT) {
            XMFLOAT2 prevScroll = scroll;
            if (Child && Child->Size.Height == Size.Height) {
                Scroll = { Scroll.x + Size.Width, Scroll.y };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    onScrolled();
                }
            } else {
                Scroll = { Scroll.x , Scroll.y + Size.Height };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    onScrolled();
                }
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.KeyCode == VK_PRIOR) {
            XMFLOAT2 prevScroll = scroll;
            if (Child && Child->Size.Height == Size.Height) {
                Scroll = { Scroll.x - Size.Width, Scroll.y };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    onScrolled();
                }
            } else {
                Scroll = { Scroll.x, Scroll.y - Size.Height };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    onScrolled();
                }
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.KeyCode == VK_HOME) {
            XMFLOAT2 prevScroll = scroll;
            Scroll = { 0.0f,0.0f };
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                onScrolled();
            }
            return true;
        } else if (event.Action == Ghurund::Core::KeyAction::DOWN && event.KeyCode == VK_END) {
            XMFLOAT2 prevScroll = scroll;
            Scroll = MaxScroll;
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                onScrolled();
            }
            return true;
        }
        return false;
    }
    
    bool ScrollView::onMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (Child) {
            XMFLOAT2 prevScroll = scroll;
            if (event.Wheel == MouseWheel::HORIZONTAL || Child->Size.Height == Size.Height) {
                scroll.x = std::max(0.0f, std::min(scroll.x - event.Delta, maxScroll.x));
            } else if (event.Wheel == MouseWheel::VERTICAL) {
                scroll.y = std::max(0.0f, std::min(scroll.y - event.Delta, maxScroll.y));
            }
            if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                repaint();
                onScrolled();
            }
        }
        return mouseWheelEvent(event);
    }
}
