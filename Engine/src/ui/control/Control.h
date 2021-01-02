#pragma once

#include "core/Event.h"
#include "core/SharedPointer.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/Canvas.h"
#include "ui/PreferredSize.h"
#include "application/Window.h"
#include "ui/UIContext.h"

#include "D2d1helper.h"
#include <tinyxml2.h>

namespace Ghurund::UI {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::UI);

    class Control;
    class ControlParent;
    class Theme;
    class LayoutLoader;

    typedef std::function<bool(Control&)> StateHandler;

    class Control: public Pointer, public Input::EventConsumer {
    private:
        ControlParent* parent = nullptr;

        FloatSize size = { 0, 0 };  // what was finally mediated

        bool visible = true;
        bool enabled = true;
        bool focusable = false;

        AString* name = nullptr;

        bool transformationInvalid = true;

        inline void rebuildTransformation() {
            transformation = D2D1::Matrix3x2F::Translation(std::round(-size.width / 2), std::round(-size.height / 2))
                * D2D1::Matrix3x2F::Rotation(rotation)
                * D2D1::Matrix3x2F::Scale(scale.x, scale.y)
                * D2D1::Matrix3x2F::Translation(std::round(position.x + size.width / 2), std::round(position.y + size.height / 2));
            transformationInvalid = false;
        }

    protected:
        XMFLOAT2 position = { 0,0 }, scale = { 1,1 };
        float rotation = 0;
        D2D1::Matrix3x2F transformation;

        FloatSize minSize = { 0,0 };
        PreferredSize preferredSize;   // what the user wants
        FloatSize measuredSize;  // what the view wants
        bool needsLayout = true;

        Theme* localTheme = nullptr;
        UIContext* context = nullptr;

        Event<Control> onSizeChanged = Event<Control>(*this);
        Event<Control> onStateChanged = Event<Control>(*this);
        Event<Control> onThemeChanged = Event<Control>(*this);
        Event<Control> onContextChanged = Event<Control>(*this);

        virtual void onMeasure(float parentWidth, float parentHeight);

        virtual void onLayout(float x, float y, float width, float height) {}

        virtual void onDraw(Canvas& canvas) {}

        virtual bool onMouseButtonEvent(const Input::MouseButtonEventArgs& event) override {
            if (focusable && event.Action == Input::MouseAction::DOWN && !Focused)
                requestFocus();
            return false;
        }

        virtual ~Control() = 0 {
            delete name;
        }

        static const Ghurund::Type& GET_TYPE();

    public:
        inline Event<Control>& getOnStateChanged() {
            return onStateChanged;
        }

        __declspec(property(get = getOnStateChanged)) Event<Control>& OnStateChanged;

        inline Event<Control>& getOnThemeChanged() {
            return onThemeChanged;
        }

        __declspec(property(get = getOnThemeChanged)) Event<Control>& OnThemeChanged;


        inline Event<Control>& getOnContextChanged() {
            return onContextChanged;
        }

        __declspec(property(get = getOnContextChanged)) Event<Control>& OnContextChanged;

        inline const AString* getName() const {
            return name;
        }

        inline void setName(const AString* name) {
            if (this->name)
                delete this->name;
            if (name)
                this->name = ghnew AString(*name);
        }

        inline void setName(const AString& name) {
            if (this->name)
                delete this->name;
            this->name = ghnew AString(name);
        }

        __declspec(property(get = getName, put = setName)) AString* Name;

        inline bool isVisible() const {
            return visible;
        }

        inline void setVisible(bool visible) {
            this->visible = visible;
            if (!visible && Focused) {
                clearFocus();
            } else {
                onStateChanged();
            }
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
            return enabled && visible && focusable;
        }

        inline void setFocusable(bool focusable) {
            this->focusable = focusable;
            if (!Focusable)
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

        virtual bool focusUp();

        virtual bool focusDown();

        virtual bool focusLeft();

        virtual bool focusRight();

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

        inline const D2D1::Matrix3x2F& getTransformation() const {
            return transformation;
        }

        __declspec(property(get = getTransformation)) const D2D1::Matrix3x2F& Transformation;

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

        inline Control* withPreferredSize(const PreferredSize& size) {
            setPreferredSize(size);
            return this;
        }

        __declspec(property(get = getPreferredSize, put = setPreferredSize)) PreferredSize& PreferredSize;

        inline const FloatSize& getMeasuredSize() const {
            return measuredSize;
        }

        __declspec(property(get = getMeasuredSize)) FloatSize& MeasuredSize;

        inline bool canReceiveEvent(const Input::MouseEventArgs& event) {
            return Visible && Enabled && hitTest((float)event.Position.x, (float)event.Position.y);
        }

        // TODO: support matrix transformation
        inline bool hitTest(float x, float y) {
            return x >= position.x && x < position.x + size.width && y >= position.y && y < position.y + size.height;
        }

        inline void setParent(ControlParent* parent) {
            this->parent = parent;
            dispatchContextChanged();
        }

        inline ControlParent* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) ControlParent* Parent;

        void setTheme(Theme* theme);

        inline Theme* getTheme() {
            if (localTheme)
                return localTheme;
            if (context)
                return &context->Theme;
            return nullptr;
        }

        __declspec(property(get = getTheme, put = setTheme)) Theme* Theme;

        inline UIContext* getContext() {
            return context;
        }

        __declspec(property(get = getContext, put = setContext)) UIContext* Context;

        virtual void dispatchContextChanged();

        virtual void repaint();

        virtual void invalidate();

        inline void measure(float parentWidth, float parentHeight) {
            if (needsLayout || (float)preferredSize.width < 0 || (float)preferredSize.height < 0) {
                if (parentWidth > 0 && parentHeight > 0) {
                    onMeasure(parentWidth, parentHeight);
                } else {
                    measuredSize = { 0,0 };
                }
            }
        }

        void layout(float x, float y, float width, float height);

        virtual void onUpdate(const uint64_t time) {}

        void draw(Canvas& canvas);

        virtual Control* find(const String& name) {
            if (this->name && this->name->operator==(name))
                return this;
            return nullptr;
        }

        virtual XMFLOAT2 getPositionInWindow();

        __declspec(property(get = getPositionInWindow)) XMFLOAT2 PositionInWindow;

        XMFLOAT2 getPositionOnScreen();

        __declspec(property(get = getPositionOnScreen)) XMFLOAT2 PositionOnScreen;

        virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml);

#ifdef _DEBUG
        virtual String logTree();
#endif

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    template<class T>
    concept IsControl = std::is_base_of<Control, T>::value;
}