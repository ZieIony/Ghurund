#pragma once

#include "core/Event.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/Canvas.h"
#include "ui/LayoutSize.h"

namespace Ghurund {
    class Control: public Pointer, public EventConsumer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Control);

    protected:
        Control* parent = nullptr;
        XMFLOAT2 position = { 0,0 };
        XMFLOAT2 minSize = { 0,0 };
        XMFLOAT2 desiredSize = { LayoutSize::WRAP_CONTENT,LayoutSize::WRAP_CONTENT };   // what the user wants
        XMFLOAT2 measuredSize = { 0,0 };  // what the view wants
        XMFLOAT2 size = { 0,0 };  // what was finally mediated
        Paint paint;

        bool visible = true;
        bool enabled = true;
        Event<Control> onStateChanged;

        static inline const float MAX_SIZE = 32768.0f;

    public:
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

        inline XMFLOAT2& getDesiredSize() {
            return desiredSize;
        }

        inline void setDesiredSize(XMFLOAT2& size) {
            this->desiredSize = size;
        }

        virtual void setDesiredSize(float width, float height) {
            desiredSize.x = width;
            desiredSize.y = height;
        }

        __declspec(property(get = getDesiredSize, put = setDesiredSize)) XMFLOAT2& DesiredSize;

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

        virtual void measure();

        virtual void layout(float x, float y, float width, float height) {
            position.x = x;
            position.y = y;
            size.x = width;
            size.y = height;
        }

        virtual void draw(Canvas& canvas) = 0;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Control>(NAMESPACE_NAME, CLASS_NAME);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}