#pragma once

#include "application/Settings.h"
#include "core/Event.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/collection/Array.h"
#include "core/threading/FunctionQueue.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"
#include "graphics/Graphics.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/Size.h"

#pragma warning(push, 0)
#include "d3dx12.h"
#pragma warning(pop)

namespace Ghurund {
    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Application;

    class Window: public ParameterProvider, public NamedObject<String>, public Object {
    private:
        String title;
        bool visible;
        POINT position;
        UI::IntSize size;

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

        Event<Window> onCreated = Event<Window>(*this);
        Event<Window> onPositionChanged = Event<Window>(*this);
        Event<Window> onSizeChanged = Event<Window>(*this);
        Event<Window> onFocusedChanged = Event<Window>(*this);
        Event<Window, const Timer&> onUpdate = Event<Window, const Timer&>(*this);
        Event<Window> onPaint = Event<Window>(*this);
        Event<Window> onDestroy = Event<Window>(*this);

        Event<Window, KeyEventArgs> onKeyEvent = Event<Window, KeyEventArgs>(*this);
        Event<Window, MouseButtonEventArgs> onMouseButtonEvent = Event<Window, MouseButtonEventArgs>(*this);
        POINT prevMousePos = { -1, -1 };
        Event<Window, MouseMotionEventArgs> onMouseMotionEvent = Event<Window, MouseMotionEventArgs>(*this);
        Event<Window, MouseWheelEventArgs> onMouseWheelEvent = Event<Window, MouseWheelEventArgs>(*this);

        Application* application;
        Window* parent;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Window))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::TYPE);

            return TYPE;
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

        virtual void setVisible(bool visible) {
            this->visible = visible;
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        Event<Window>& getOnCreated() {
            return onCreated;
        }

        __declspec(property(get = getOnCreated)) Event<Window>& OnCreated;

        Event<Window>& getOnDestroy() {
            return onDestroy;
        }

        __declspec(property(get = getOnDestroy)) Event<Window>& OnDestroy;

        Event<Window, const Timer&>& getOnUpdate() {
            return onUpdate;
        }

        __declspec(property(get = getOnUpdate)) Event<Window, const Timer&>& OnUpdate;

        Event<Window>& getOnPaint() {
            return onPaint;
        }

        __declspec(property(get = getOnPaint)) Event<Window>& OnPaint;

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

        Event<Window>& getOnPositionChanged() {
            return onPositionChanged;
        }

        __declspec(property(get = getOnPositionChanged)) Event<Window>& OnPositionChanged;

        Event<Window>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<Window>& OnSizeChanged;

        virtual bool isFocused() const {
            return false;
        }

        __declspec(property(get = isFocused)) bool Focused;

        Event<Window>& getOnFocusedChanged() {
            return onFocusedChanged;
        }

        __declspec(property(get = getOnFocusedChanged)) Event<Window>& OnFocusedChanged;

        Event<Window, KeyEventArgs>& getOnKeyEvent() {
            return onKeyEvent;
        }

        __declspec(property(get = getOnKeyEvent)) Event<Window, KeyEventArgs>& OnKeyEvent;

        Event<Window, MouseButtonEventArgs>& getOnMouseButtonEvent() {
            return onMouseButtonEvent;
        }

        __declspec(property(get = getOnMouseButtonEvent)) Event<Window, MouseButtonEventArgs>& OnMouseButtonEvent;

        Event<Window, MouseMotionEventArgs>& getOnMouseMotionEvent() {
            return onMouseMotionEvent;
        }

        __declspec(property(get = getOnMouseMotionEvent)) Event<Window, MouseMotionEventArgs>& OnMouseMotionEvent;

        Event<Window, MouseWheelEventArgs>& getOnMouseWheelEvent() {
            return onMouseWheelEvent;
        }

        __declspec(property(get = getOnMouseWheelEvent)) Event<Window, MouseWheelEventArgs>& OnMouseWheelEvent;

        virtual void refresh() const {}

        virtual void activate() const {}

        inline Application* getApplication() {
            return application;
        }

        inline void setApplication(Application* application) {
            this->application = application;
        }

        __declspec(property(get = getApplication, put = setApplication)) Application* Application;

        inline Window* getParent() {
            return parent;
        }

        __declspec(property(get = getParent)) Window* Parent;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}