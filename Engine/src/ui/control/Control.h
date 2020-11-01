#pragma once

#include "core/Event.h"
#include "core/ScopedPointer.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/Canvas.h"
#include "ui/PreferredSize.h"
#include "ui/Cursor.h"
#include "application/Window.h"

namespace Ghurund::UI {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::UI);

    class Control;
    class ControlParent;

    typedef std::function<bool(Control&)> StateHandler;

    class Control: public Pointer, public EventConsumer {
    private:
        ControlParent* parent = nullptr;

        FloatSize size = { 0, 0 };  // what was finally mediated

        bool visible = true;
        bool enabled = true;
        bool focusable = false;

        ASCIIString* name = nullptr;

        DrawingCache* cache = nullptr;
        bool transformationInvalid = true;

        inline void rebuildTransformation() {
            transformation->Reset();
            transformation->Translate(-size.width / 2, -size.height / 2);
            transformation->Rotate(rotation);
            transformation->Scale(scale.x, scale.y);
            transformation->Translate(position.x + size.width / 2, position.y + size.height / 2);
            transformationInvalid = false;
        }

    protected:
        XMFLOAT2 position = { 0,0 }, scale = { 1,1 };
        float rotation = 0;
        Gdiplus::Matrix* transformation;

        FloatSize minSize = { 0,0 };
        PreferredSize preferredSize;   // what the user wants
        FloatSize measuredSize;  // what the view wants
        bool needsLayout = true;
        bool cacheEnabled = false;

        Event<Control> onSizeChanged = Event<Control>(*this);

        virtual void onMeasure(float parentWidth, float parentHeight);

        virtual void onLayout(float x, float y, float width, float height) {}

        virtual void onDraw(Canvas& canvas) {}

        virtual void onStateChanged();

        ~Control() = 0 {
            delete name;
            delete transformation;
            delete cache;
        }

    public:
        Control() {
            transformation = new Gdiplus::Matrix();
        }

        inline const ASCIIString* getName() const {
            return name;
        }

        inline void setName(const ASCIIString* name) {
            if (this->name)
                delete this->name;
            if (name)
                this->name = ghnew ASCIIString(*name);
        }

        inline void setName(const ASCIIString& name) {
            if (this->name)
                delete this->name;
            this->name = ghnew ASCIIString(name);
        }

        __declspec(property(get = getName, put = setName)) ASCIIString* Name;

        inline bool isVisible() const {
            return visible;
        }

        inline void setVisible(bool visible) {
            this->visible = visible;
            onStateChanged();
        }

        __declspec(property(get = isVisible, put = setVisible)) bool Visible;

        inline bool isEnabled() const {
            return enabled;
        }

        inline void setEnabled(bool enabled) {
            if (this->enabled == enabled)
                return;
            this->enabled = enabled;
            if (!enabled && Focused) {
                clearFocus();
            } else {
                onStateChanged();
            }
        }

        __declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

        inline bool isFocusable() const {
            return focusable;
        }

        inline void setFocusable(bool focusable) {
            this->focusable = focusable;
            if (!focusable)
                clearFocus();
        }

        __declspec(property(get = isFocusable, put = setFocusable)) bool Focusable;

        virtual Control* getFocus() {
            return focusable ? this : nullptr;
        }

        __declspec(property(get = getFocus)) Control* Focus;

        void requestFocus();

        void clearFocus();

        virtual bool isFocused() const;

        __declspec(property(get = isFocused)) bool Focused;

        virtual bool focusNext();

        virtual bool focusPrevious();

        inline const XMFLOAT2& getPosition() const {
            return position;
        }

        inline void setPosition(const XMFLOAT2& position) {
            this->position = position;
            transformationInvalid = true;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
            transformationInvalid = true;
        }

        __declspec(property(get = getPosition, put = setPosition)) const XMFLOAT2& Position;

        inline float getRotation() const {
            return rotation;
        }

        inline void setRotation(float rotation) {
            this->rotation = rotation;
            transformationInvalid = true;
        }

        __declspec(property(get = getRotation, put = setRotation)) float Rotation;

        inline const XMFLOAT2& getScale() const {
            return scale;
        }

        inline void setScale(const XMFLOAT2& scale) {
            this->scale = scale;
            transformationInvalid = true;
        }

        inline void setScale(float x, float y) {
            position.x = x;
            position.y = y;
            transformationInvalid = true;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT2& Scale;

        inline Gdiplus::Matrix& getTransformation() const {
            return *transformation;
        }

        __declspec(property(get = getTransformation)) Gdiplus::Matrix& Transformation;

        inline FloatSize& getMinSize() {
            return minSize;
        }

        inline void setMinSize(const FloatSize& size) {
            this->minSize = size;
        }

        virtual void setMinSize(float width, float height) {
            minSize.width = abs(width);
            minSize.height = abs(height);
        }

        __declspec(property(get = getMinSize, put = setMinSize)) FloatSize& MinSize;

        inline const FloatSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) FloatSize& Size;

        inline Event<Control>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<Control>& OnSizeChanged;

        inline PreferredSize& getPreferredSize() {
            return preferredSize;
        }

        inline void setPreferredSize(const PreferredSize& size) {
            this->preferredSize = size;
        }

        virtual void setPreferredSize(const PreferredSize::Width& width, const PreferredSize::Height& height) {
            preferredSize.width = width;
            preferredSize.height = height;
        }

        __declspec(property(get = getPreferredSize, put = setPreferredSize)) PreferredSize& PreferredSize;

        inline const FloatSize& getMeasuredSize() const {
            return measuredSize;
        }

        __declspec(property(get = getMeasuredSize)) FloatSize& MeasuredSize;

        inline bool canReceiveEvent(const MouseEventArgs& event) {
            return Visible && Enabled &&
                event.Position.x >= position.x && event.Position.x < position.x + Size.width &&
                event.Position.y >= position.y && event.Position.y < position.y + Size.height;
        }

        // TODO: support matrix transformation
        inline bool hitTest(float x, float y) {
            return x >= position.x && x < position.x + size.width && y >= position.y && y < position.y + size.height;
        }

        void setParent(ControlParent* parent) {
            this->parent = parent;
        }

        ControlParent* getParent()const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) ControlParent* Parent;

        virtual Window* getWindow() const;

        __declspec(property(get = getWindow)) Window* Window;

        inline void invalidateCache() {
            delete cache;
            cache = nullptr;
        }

        virtual void repaint();

        virtual void invalidate();

        inline void measure(float parentWidth, float parentHeight) {
            if (needsLayout || (float)preferredSize.width < 0 || (float)preferredSize.height < 0)
                onMeasure(parentWidth, parentHeight);
        }

        void layout(float x, float y, float width, float height);

        virtual void update(const Timer& timer) {}

        void draw(Canvas& canvas);

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            if (focusable && event.Action == MouseAction::DOWN && !Focused)
                requestFocus();
            return __super::dispatchMouseButtonEvent(event);
        }

        virtual Control* find(const String& name) {
            if (this->name && this->name->operator==(name))
                return this;
            return nullptr;
        }

        virtual XMFLOAT2 getPositionInWindow();

        __declspec(property(get = getPositionInWindow)) XMFLOAT2 PositionInWindow;

        XMFLOAT2 getPositionOnScreen();

        __declspec(property(get = getPositionOnScreen)) XMFLOAT2 PositionOnScreen;

        static const Ghurund::Type& TYPE();

        virtual const Ghurund::Type& getType() const override {
            return Control::TYPE();
        }
    };

    typedef ScopedPointer<Control> ControlPtr;

    template<class T>
    concept IsControl = std::is_base_of<Control, T>::value;
}