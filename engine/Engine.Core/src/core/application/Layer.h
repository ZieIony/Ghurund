#pragma once

#include "DrawingContext.h"
#include "core/RefCountedObject.h"
#include "core/input/Keyboard.h"
#include "core/input/Mouse.h"
#include "core/math/Size.h"

namespace Ghurund::Core {

    class Layer:public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Layer::GET_TYPE();
#pragma endregion

    private:
        IntSize size = { 0,0 };
        bool focused = false;

    protected:
        virtual bool onSizeChanged() {
            return false;
        }

        virtual bool onFocusedChanged() {
            return false;
        }

    public:
		virtual ~Layer() = 0 {}

        inline void setSize(const IntSize& size) {
            if (this->size != size) {
                this->size = size;
                onSizeChanged();
            }
        }

        inline const IntSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline void setFocused(bool focused) {
            if (this->focused != focused) {
                this->focused = focused;
                onFocusedChanged();
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

        virtual void draw(IDrawingContext& context) {}
    };
}