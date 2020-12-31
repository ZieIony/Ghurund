#pragma once

#include "application/Settings.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/collection/Array.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"
#include "graphics/Graphics.h"
#include "input/EventConsumer.h"
#include "ui/Size.h"

#pragma warning(push, 0)
#include "d3dx12.h"
#pragma warning(pop)

namespace Ghurund {
    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Input;

    class Window: public ParameterProvider, public NamedObject<String>, public Object, public EventConsumer {
    private:
        String title;
        bool visible = false;
        POINT position = {};
        UI::IntSize size = {};

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

        POINT prevMousePos = { -1, -1 };

        Window* parent;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Window))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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

        virtual void updateParameters() override {
            XMFLOAT2 sizeParam = { (float)size.width, (float)size.height };
            parameterViewportSize->setValue(&sizeParam);
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        virtual void setTitle(const String& title) {
            this->title = title;
        }

        inline const String& getTitle()const {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) String& Title;

        virtual HWND getHandle() const {
            return parent->Handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        virtual Input& getInput() {
            return parent->Input;
        }

        __declspec(property(get = getInput)) Input& Input;

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

        inline const POINT& getPosition() const {
            return position;
        }

        inline void setPosition(const POINT& position) {
            setPosition(position.x, position.y);
        }

        virtual void setPosition(int x, int y) {
            position = { x,y };
        }

        __declspec(property(get = getPosition, put = setPosition)) POINT& Position;

        inline const UI::IntSize& getSize() const {
            return size;
        }

        inline void setSize(const UI::IntSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(unsigned int w, unsigned int h) {
            size = { w, h };
        }

        __declspec(property(get = getSize, put = setSize)) UI::IntSize& Size;

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