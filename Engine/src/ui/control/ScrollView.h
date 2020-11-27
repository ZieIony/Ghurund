#pragma once

#include "ControlContainer.h"

#include <algorithm>

namespace Ghurund::UI {
    class ScrollView:public ControlContainer {
    private:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ScrollView>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ScrollView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

        XMFLOAT2 scroll = { 0.0f, 0.0f };
        XMFLOAT2 maxScroll = { 0.0f, 0.0f };
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

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

        virtual void onDraw(Canvas& canvas) override {
            canvas.save();
            canvas.clipRect(0, 0, Size.width, Size.height);
            canvas.translate(-scroll.x, -scroll.y);
            __super::onDraw(canvas);
            canvas.restoreClipRect();
            canvas.restore();
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (Child) {
                Child->layout(0, 0,
                    Child->PreferredSize.width == PreferredSize::Width::FILL ? width : Child->MeasuredSize.width,
                    Child->PreferredSize.height == PreferredSize::Height::FILL ? height : Child->MeasuredSize.height);
                maxScroll = {
                    std::max(0.0f, Child->Size.width - Size.width),
                    std::max(0.0f, Child->Size.height - Size.height)
                };
                scroll = {
                    std::max(0.0f, std::min(scroll.x, maxScroll.x)),
                    std::max(0.0f, std::min(scroll.y, maxScroll.y))
                };
            }
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            if (event.Action == KeyAction::DOWN && event.Key == VK_NEXT) {
                XMFLOAT2 prevScroll = scroll;
                if (Child && Child->Size.height == Size.height) {
                    Scroll = { Scroll.x + Size.width, Scroll.y };
                    if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                        repaint();
                        OnScrolled();
                    }
                } else {
                    Scroll = { Scroll.x , Scroll.y + Size.height };
                    if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                        repaint();
                        OnScrolled();
                    }
                }
                return true;
            } else if (event.Action == KeyAction::DOWN && event.Key == VK_PRIOR) {
                XMFLOAT2 prevScroll = scroll;
                if (Child && Child->Size.height == Size.height) {
                    Scroll = { Scroll.x - Size.width, Scroll.y };
                    if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                        repaint();
                        OnScrolled();
                    }
                } else {
                    Scroll = { Scroll.x, Scroll.y - Size.height };
                    if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                        repaint();
                        OnScrolled();
                    }
                }
                return true;
            } else if (event.Action == KeyAction::DOWN && event.Key == VK_HOME) {
                XMFLOAT2 prevScroll = scroll;
                Scroll = { 0.0f,0.0f };
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
                return true;
            } else if (event.Action == KeyAction::DOWN && event.Key == VK_END) {
                XMFLOAT2 prevScroll = scroll;
                Scroll = MaxScroll;
                if (prevScroll.x != scroll.x || prevScroll.y != scroll.y) {
                    repaint();
                    OnScrolled();
                }
                return true;
            }
            return __super::dispatchKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return __super::dispatchMouseButtonEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event.translate(scroll.x, scroll.y, event.Inside));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            if (Child) {
                XMFLOAT2 prevScroll = scroll;
                if (event.Wheel == MouseWheel::HORIZONTAL || Child->Size.height == Size.height) {
                    scroll.x = std::max(0.0f, std::min(scroll.x - event.Delta, maxScroll.x));
                } else if (event.Wheel == MouseWheel::VERTICAL) {
                    scroll.y = std::max(0.0f, std::min(scroll.y - event.Delta, maxScroll.y));
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
}