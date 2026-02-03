#pragma once

#include "core/Color.h"
#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "core/math/Point.h"
#include "core/math/Size.h"
#include "core/object/Object.h"
#include "core/reflection/Type.h"
#include "Cursor.h"

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
        XMINT2 position = {};
        bool focused = false, visible = false;
        String title = {};
        std::unique_ptr<Color> backgroundColor;
        const Cursor* cursor = &Cursor::ARROW;

        /*
        Array<SharedPointer<Parameter>> parameters;
        ValueParameter* parameterViewportSize = nullptr;
        */
        XMINT2 prevMousePos = { -1, -1 };

        Window* parent;

        Window& operator=(const Window& other) = delete;

    protected:
        virtual bool onPositionChanged() {
            return false;
        }

        virtual bool onSizeChanged() {
            return false;
        }

        virtual bool onFocusedChanged() {
            return false;
        }

        virtual bool onVisibleChanged() {
            return false;
        }

        virtual bool onClosed() {
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

        virtual ~Window() = 0 {}
        /*
        virtual void initParameters(ParameterManager& parameterManager) override {
            if (parameterViewportSize != nullptr)
                return;

            parameters.set(0, parameterViewportSize = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEWPORT_SIZE.Value]);
        }

        virtual void updateParameters() override;

        virtual const Array<SharedPointer<Parameter>>& getParameters() const override {
            return parameters;
        }
        */

        virtual HWND getHandle() const {
            return parent->Handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline const Cursor& getCursor() const {
            return *cursor;
        }

        inline void setCursor(const Cursor& cursor) {
            this->cursor = &cursor;
        }

        __declspec(property(get = getCursor, put = setCursor)) const Cursor& Cursor;

        // not null
        virtual Ghurund::Core::Input* getInput() {
            return parent->Input;
        }

        __declspec(property(get = getInput)) Ghurund::Core::Input* Input;

        // not null
        virtual Timer& getTimer() const {
            return parent->Timer;
        }

        __declspec(property(get = getTimer)) Timer& Timer;

        virtual void setTitle(const String& title) {
            this->title = title;
        }

        const String& getTitle() const {
            return title;
        }

        __declspec(property(get = getTitle, put = setTitle)) const String& Title;

        inline const Color* getBackgroundColor() const {
            return backgroundColor.get();
        }

        inline void setBackgroundColor(const Color* color) {
            if (color) {
                this->backgroundColor.reset(ghnew Color(*color));
            } else {
                this->backgroundColor.reset();
            }
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) const Color* BackgroundColor;

        virtual void setVisible(bool visible) {
            this->visible = visible;
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        inline const XMINT2& getPosition() const {
            return position;
        }

        virtual void setPosition(const XMINT2& position) {
			if (this->position.x != position.x || this->position.y != position.y) {
                this->position = position;
                dispatchPositionChangedEvent();
            }
        }

        inline void setPosition(int32_t x, int32_t y) {
            setPosition({ x, y });
        }

        __declspec(property(get = getPosition, put = setPosition)) const XMINT2& Position;

        inline bool dispatchPositionChangedEvent() {
            bool result = onPositionChanged();
            bool result2 = positionChanged();
            return result || result2;
        }

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            if (this->size != size) {
                this->size = size;
                dispatchSizeChangedEvent();
            }
        }

        inline void setSize(uint32_t w, uint32_t h) {
            setSize({ w, h });
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline bool dispatchSizeChangedEvent() {
            bool result = onSizeChanged();
            bool result2 = sizeChanged();
            return result || result2;
        }

        virtual void setClientPosition(const XMINT2& pos) {
            setPosition(pos.x, pos.y);
        }

        virtual XMINT2 getClientPosition() {
            return Position;
        }

        __declspec(property(get = getClientPosition, put = setClientPosition)) XMINT2 ClientPosition;

        virtual void setClientSize(const IntSize& size) {
            setSize(size);
        }

        virtual IntSize getClientSize() {
            return Size;
        }

        __declspec(property(get = getClientSize, put = setClientSize)) IntSize ClientSize;

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
            bool result = onFocusedChanged();
            bool result2 = focusedChanged();
            return result || result2;
        }

        inline bool dispatchClosedEvent() {
            bool result = onClosed();
            bool result2 = closed();
            return result || result2;
        }

        virtual void update() {}

        virtual void paint() {}
  };
}