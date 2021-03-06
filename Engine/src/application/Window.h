#pragma once

#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/reflection/Type.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"
#include "input/EventConsumer.h"
#include "core/math/Point.h"
#include "core/math/Size.h"

namespace Ghurund::Input {
    class Input;
}

namespace Ghurund {
    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Timer;

    class Window: public ParameterProvider, public NamedObject, public Object, public Input::EventConsumer {
    private:
        WString title;
        bool visible = false;
        IntPoint position = {};
        IntSize size = {};

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

        IntPoint prevMousePos = { -1, -1 };

        Window* parent;

    protected:
        Event<Window> onPositionChanged = *this;
        virtual bool onPositionChangedEvent() {
            return false;
        }

        Event<Window> onSizeChanged = *this;
        virtual bool onSizeChangedEvent() {
            return false;
        }

        Event<Window> onFocusedChanged = *this;
        virtual bool onFocusedChangedEvent() {
            return false;
        }

        virtual void onUpdate(const uint64_t time) {}
        virtual void onPaint() {}

        Event<Window> onClosed = *this;
        virtual bool onClosedEvent() {
            return false;
        }

        static const Ghurund::Type& GET_TYPE();

    public:
        Window(Window* parent = nullptr):parameters(PointerArray<Parameter*>(1)) {
            this->parent = parent;
        }

        ~Window() = 0 {}

        virtual void initParameters(ParameterManager& parameterManager) override {
            if (parameterViewportSize != nullptr)
                return;

            parameters.set(0, parameterViewportSize = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEWPORT_SIZE.Value]);
        }

        virtual void updateParameters() override;

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        virtual void setTitle(const WString& title) {
            this->title = title;
        }

        inline const WString& getTitle()const {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) WString& Title;

        virtual HWND getHandle() const {
            return parent->Handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        virtual Input::Input& getInput() {
            return parent->Input;
        }

        __declspec(property(get = getInput)) Input::Input& Input;

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

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(unsigned int w, unsigned int h) {
            size = { w, h };
        }

        __declspec(property(get = getSize, put = setSize)) IntSize& Size;

        virtual bool isFocused() const {
            return false;
        }

        __declspec(property(get = isFocused)) bool Focused;

        virtual void refresh() const {}

        virtual void activate() const {}

        inline Window* getParent() {
            return parent;
        }

        __declspec(property(get = getParent)) Window* Parent;

        inline Event<Window>& getOnPositionChanged() {
            return onPositionChanged;
        }

        __declspec(property(get = getOnPositionChanged)) Event<Window>& OnPositionChanged;

        inline bool dispatchPositionChangedEvent() {
            bool result = onPositionChangedEvent();
            bool result2 = onPositionChanged();
            return result || result2;
        }

        inline Event<Window>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<Window>& onSizeChanged;

        inline bool dispatchSizeChangedEvent() {
            bool result = onSizeChangedEvent();
            bool result2 = onSizeChanged();
            return result || result2;
        }

        inline Event<Window>& getOnFocusedChanged() {
            return onFocusedChanged;
        }

        __declspec(property(get = getOnFocusedChanged)) Event<Window>& OnFocusedChanged;

        inline bool dispatchFocusedChangedEvent() {
            bool result = onFocusedChangedEvent();
            bool result2 = onFocusedChanged();
            return result || result2;
        }

        inline Event<Window>& getOnClosed() {
            return onClosed;
        }

        __declspec(property(get = getOnClosed)) Event<Window>& OnClosed;

        inline bool dispatchClosedEvent() {
            bool result = onClosedEvent();
            bool result2 = onClosed();
            return result || result2;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}