#pragma once

#include "Status.h"
#include "core/input/Keyboard.h"
#include "core/input/Mouse.h"
#include "core/math/Size.h"
#include "graphics/buffer/RenderTarget.h"

namespace Ghurund {
    class Layer {
    private:
        IntSize size = { 0,0 };
        bool focused = false;

        virtual bool onSizeChangedEvent() {
            return false;
        }

        virtual bool onFocusedChangedEvent() {
            return false;
        }

    public:
        virtual ~Layer() = 0 {}

        inline void setSize(const IntSize& size) {
            if (this->size.width != size.width || this->size.height != size.height) {
                this->size = size;
                onSizeChangedEvent();
            }
        }

        inline const IntSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline void setFocused(bool focused) {
            if (this->focused != focused) {
                this->focused = focused;
                onFocusedChangedEvent();
            }
        }

        inline bool isFocused() const {
            return focused;
        }

        __declspec(property(get = isFocused, put = setFocused)) bool Focused;

        virtual bool dispatchKeyEvent(const KeyEventArgs& args) {
            return false;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
            return false;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            return false;
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            return false;
        }

        virtual void update(const uint64_t time) {}

        virtual Status draw(RenderTarget& renderTarget) {
            return Status::OK;
        }
    };
}