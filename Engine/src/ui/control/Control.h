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
        inline static const char* CLASS_NAME = GH_STRINGIFY(Control);

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
        ControlParent* parent = nullptr;

        XMFLOAT2 position = { 0,0 }, scale = { 1,1 };
        float rotation = 0;
        Gdiplus::Matrix* transformation;

        FloatSize minSize = { 0,0 };
        PreferredSize preferredSize;   // what the user wants
        FloatSize measuredSize;  // what the view wants
        FloatSize size = { 0, 0 };  // what was finally mediated
        bool needsLayout = true;
        bool cacheEnabled = false;

        bool visible = true;
        bool enabled = true;
        bool focused = false;

        String* name = nullptr;

        virtual void onMeasure(float parentWidth, float parentHeight);

        virtual void onLayout(float x, float y, float width, float height) {}

        virtual void onDraw(Canvas& canvas) {}

        virtual void onStateChanged();

        ~Control() {
            delete name;
            delete transformation;
            delete cache;
        }

    public:
        Control() {
            transformation = new Gdiplus::Matrix();
        }

        inline const String* getName() const {
            return name;
        }

        inline void setName(const String* name) {
            if (this->name)
                delete this->name;
            if (name)
                this->name = ghnew String(*name);
        }

        inline void setName(const String& name) {
            if (this->name)
                delete this->name;
            this->name = ghnew String(name);
        }

        __declspec(property(get = getName, put = setName)) String* Name;

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
            this->enabled = enabled;
            onStateChanged();
        }

        __declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

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

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2& Position;

        inline const float getRotation() const {
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

        inline void setMinSize(FloatSize& size) {
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

        inline PreferredSize& getPreferredSize() {
            return preferredSize;
        }

        inline void setPreferredSize(PreferredSize& size) {
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

        void requestFocus();

        virtual void clearFocus() {
            if (!focused)
                return;
            focused = false;
            onStateChanged();
        }

        inline bool isFocused() const {
            return focused;
        }

        __declspec(property(get = isFocused)) bool Focused;

        inline void measure(float parentWidth, float parentHeight) {
            if (needsLayout || (float)preferredSize.width < 0 || (float)preferredSize.height < 0)
                onMeasure(parentWidth, parentHeight);
        }

        void layout(float x, float y, float width, float height);

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

        inline static const Ghurund::Type& TYPE = TypeBuilder<Control>(NAMESPACE_NAME, CLASS_NAME);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<Control> ControlPtr;

    template<class T>
    concept IsControl = std::is_base_of<Control, T>::value;
}