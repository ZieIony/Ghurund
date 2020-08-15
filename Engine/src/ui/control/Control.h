#pragma once

#include "core/Event.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/Canvas.h"
#include "ui/PreferredSize.h"

namespace Ghurund::UI {
    class Control: public Pointer, public EventConsumer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Control);

    protected:
        Control* parent = nullptr;
        XMFLOAT2 position = { 0,0 };
        XMFLOAT2 minSize = { 0,0 };
        PreferredSize preferredSize;   // what the user wants
        XMFLOAT2 measuredSize;  // what the view wants
        XMFLOAT2 size = { 0, 0 };  // what was finally mediated
        Paint paint;

        bool visible = true;
        bool enabled = true;
        Event<Control> onStateChanged;

        tchar* name = nullptr;

    public:
        ~Control() {
            delete[] name;
        }

        inline const tchar* getName() const {
            return name;
        }

        inline void setName(const tchar* name) {
            safeCopyStr(&this->name, name);
        }

        __declspec(property(get = getName, put = setName)) tchar* Name;

        inline bool isVisible() const {
            return visible;
        }

        inline void setVisible(bool visible) {
            this->visible = visible;
            onStateChanged(*this);
        }

        __declspec(property(get = isVisible, put = setVisible)) bool Visible;

        inline bool isEnabled() const {
            return enabled;
        }

        inline void setEnabled(bool enabled) {
            this->enabled = enabled;
            onStateChanged(*this);
        }

        __declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

        inline const XMFLOAT2& getPosition() const {
            return position;
        }

        inline void setPosition(XMFLOAT2& position) {
            this->position = position;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2& Position;

        inline const XMFLOAT2& getMinSize() const {
            return minSize;
        }

        inline void setMinSize(XMFLOAT2& size) {
            this->minSize = size;
        }

        virtual void setMinSize(float width, float height) {
            minSize.x = abs(width);
            minSize.y = abs(height);
        }

        inline const XMFLOAT2& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) XMFLOAT2& Size;

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

        inline const XMFLOAT2& getMeasuredSize() const {
            return measuredSize;
        }

        __declspec(property(get = getMeasuredSize)) XMFLOAT2& MeasuredSize;

        Event<Control>& getOnStateChanged() {
            return onStateChanged;
        }

        __declspec(property(get = getOnStateChanged)) Event<Control>& OnStateChanged;

        void setParent(Control* parent) {
            this->parent = parent;
        }

        Control* getParent()const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) Control* Parent;

        virtual void repaint() {
            if (parent)
                parent->repaint();
        }

        virtual void invalidate() {
            if (parent)
                parent->invalidate();
        }

        virtual void measure() {
            if (preferredSize.width == PreferredSize::Width::WRAP) {
                measuredSize.x = minSize.x;
            } else if (preferredSize.width != PreferredSize::Width::FILL) {
                measuredSize.x = (float)preferredSize.width;
            }

            if (preferredSize.height == PreferredSize::Height::WRAP) {
                measuredSize.y = minSize.y;
            } else if (preferredSize.height != PreferredSize::Height::FILL) {
                measuredSize.y = (float)preferredSize.height;
            }
        }

        virtual void layout(float x, float y, float width, float height) {
            //_ASSERT_EXPR(width > 0, "Invalid width.\n");
            //_ASSERT_EXPR(height > 0, "Invalid height.\n");
            position.x = x;
            position.y = y;
            size.x = width;
            size.y = height;
        }

        virtual void draw(Canvas& canvas) = 0;

        virtual Control* find(const String& name) {
            if (this->name && name.operator==(this->name))
                return this;
            return nullptr;
        }

        virtual String save() const {
            String str;
            str = str + TYPE.Name + " {\n";
            str = str + "preferredSize: {" + (float)(preferredSize.width) + ", " + (float)(preferredSize.height) + "}\n";
            str = str + "measuredSize: {" + measuredSize.x + ", " + measuredSize.y + "}\n";
            str = str + "size: {" + size.x + ", " + size.y + "}\n";
            str = str + "}\n";
            return str;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Control>(NAMESPACE_NAME, CLASS_NAME);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}