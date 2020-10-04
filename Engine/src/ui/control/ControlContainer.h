#pragma once

#include "ControlParent.h"

namespace Ghurund::UI {
    class ControlContainer : public ControlParent {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ControlContainer);

        Control* child = nullptr;
        bool childCaptured = false;
        bool previousReceiver = false;

    public:
        ~ControlContainer() {
            if (child) {
                child->Parent = nullptr;
                child->release();
            }
        }

        inline Control* getChild() {
            return child;
        }

        inline void setChild(Control* child) {
            if (this->child)
                this->child->Parent = nullptr;
            setPointer(this->child, child);
            if (this->child)
                this->child->Parent = this;
        }

        __declspec(property(get = getChild, put = setChild)) Control* Child;

        virtual void clearFocus() {
            if (child)
                child->clearFocus();
            __super::clearFocus();
        }

        virtual Control* getFocus() override {
            return child;
        }

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override {
            if (child)
                child->layout(0, 0, width, height);
        }

        void onDraw(Canvas& canvas) {
            if (child)
                child->draw(canvas);
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);

        inline static const Ghurund::Type& TYPE = TypeBuilder<ControlContainer>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}