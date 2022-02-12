#pragma once

#include "Status.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/reflection/Type.h"
#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "core/math/Point.h"
#include "core/math/Size.h"
#include "core/Observable.h"
#include "core/window/WindowStyle.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Core {
    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Timer;

    class Window:public Object, public EventConsumer {
    private:
        /*
        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;
        */
        IntPoint prevMousePos = { -1, -1 };

        Window* parent;
        WindowStyle style = {
            .hasMinimizeButton = true,
            .hasMaximizeButton = true,
            .hasTitle = true,
            .borderStyle = WindowBorderStyle::RESIZE,
            .showOnTaskbar = true
        };

    protected:
        virtual bool onPositionChangedEvent() {
            return false;
        }

        virtual bool onSizeChangingEvent(const IntSize& size) {
            return false;
        }

        virtual bool onSizeChangedEvent() {
            return false;
        }

        virtual bool onFocusedChangedEvent() {
            return false;
        }

        virtual bool onClosedEvent() {
            return false;
        }

        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Event<Window> positionChanged = *this;
        Event<Window, IntSize> sizeChanging = *this;
        Event<Window> sizeChanged = *this;
        Event<Window> focusedChanged = *this;
        Event<Window> closed = *this;

        Observable<WString> title;
        Observable<bool> visible;
        Observable<IntSize> size;
        Observable<IntPoint> position;

        Window(Window* parent = nullptr) {
            this->parent = parent;
        }

        ~Window() = 0 {}
        /*
        virtual void initParameters(ParameterManager& parameterManager) override {
            if (parameterViewportSize != nullptr)
                return;

            parameters.set(0, parameterViewportSize = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEWPORT_SIZE.Value]);
        }

        virtual void updateParameters() override;

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }
        */

        inline WindowStyle getStyle() const {
            return style;
        }

        inline void setStyle(WindowStyle style) {
            this->style = style;
        }

        __declspec(property(get = getStyle, put = setStyle)) WindowStyle Style;

        virtual HWND getHandle() const {
            return parent->Handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        virtual Ghurund::Core::Input& getInput() {
            return parent->Input;
        }

        __declspec(property(get = getInput)) Ghurund::Core::Input& Input;

        virtual Timer& getTimer() const {
            return parent->Timer;
        }

        __declspec(property(get = getTimer)) Timer& Timer;

        virtual void setVisible(bool visible) {
            this->visible = visible;
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        inline const IntPoint& getPosition() const {
            return position;
        }

        inline void setPosition(const IntPoint& position) {
            setPosition(position.x, position.y);
        }

        virtual void setPosition(int x, int y) {
            position = { x,y };
        }

        __declspec(property(get = getPosition, put = setPosition)) IntPoint& Position;

        inline bool dispatchPositionChangedEvent() {
            bool result = onPositionChangedEvent();
            bool result2 = positionChanged();
            return result || result2;
        }

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(uint32_t w, uint32_t h) {
            size = { w, h };
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline bool dispatchSizeChangingEvent(const IntSize& size) {
            bool result = onSizeChangingEvent(size);
            bool result2 = sizeChanging(size);
            return result || result2;
        }

        inline bool dispatchSizeChangedEvent() {
            bool result = onSizeChangedEvent();
            bool result2 = sizeChanged();
            return result || result2;
        }

        virtual bool isFocused() const {
            return false;
        }

        __declspec(property(get = isFocused)) bool Focused;

        virtual void refresh() const = 0;

        virtual void bringToFront() = 0;

        virtual void sendToBack() = 0;

        inline Window* getParent() {
            return parent;
        }

        __declspec(property(get = getParent)) Window* Parent;

        inline bool dispatchFocusedChangedEvent() {
            bool result = onFocusedChangedEvent();
            bool result2 = focusedChanged();
            return result || result2;
        }

        inline bool dispatchClosedEvent() {
            bool result = onClosedEvent();
            bool result2 = closed();
            return result || result2;
        }

        virtual void update(const uint64_t time) {}

        virtual Status paint() {
            return Status::OK;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
  };
}