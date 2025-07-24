#pragma once

#include "core/object/Object.h"
#include "core/reflection/Type.h"
#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "core/math/Point.h"
#include "core/math/Size.h"
#include "core/Observable.h"
#include "core/window/WindowStyle.h"

namespace Ghurund::Core {
    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Timer;

    class Window:public Object, public EventConsumer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Window::GET_TYPE();
#pragma endregion

    private:
        IntSize size = {};
        IntPoint position = {};
        bool focused = false, visible = false;
        String title = {};

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

        virtual bool onSizeChangedEvent() {
            return false;
        }

        virtual bool onFocusedChangedEvent() {
            return false;
        }

        virtual bool onVisibleChangedEvent() {
            return false;
        }

        virtual bool onClosedEvent() {
            return false;
        }

    public:
        Event<Window> positionChanged = *this;
        Event<Window> sizeChanged = *this;
        Event<Window> visibleChanged = *this;
        Event<Window> focusedChanged = *this;
        Event<Window> closed = *this;

        Window(Window* parent = nullptr) {
            this->parent = parent;
        }

        ~Window()
        //    = 0   // TODO: a destructor cannot be abstract
        {}
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

        // not null
        virtual Ghurund::Core::Input* getInput() {
            return parent->Input;
        }

        __declspec(property(get = getInput)) Ghurund::Core::Input* Input;

        // not null
        virtual Timer* getTimer() const {
            return parent->Timer;
        }

        __declspec(property(get = getTimer)) Timer* Timer;

        virtual void setTitle(const String& title) {
            this->title = title;
        }

        const String& getTitle() const {
            return title;
        }

        __declspec(property(get = getTitle, put = setTitle)) const String& Title;

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

        virtual void setPosition(const IntPoint& position) {
            this->position = position;
        }

        inline void setPosition(int32_t x, int32_t y) {
            setPosition({ x, y });
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

        virtual void setSize(const IntSize& size) {
            this->size = size;
        }

        inline void setSize(uint32_t w, uint32_t h) {
            setSize({ w, h });
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

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

        virtual void paint() {}
  };
}