#pragma once

#include "ControlParent.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    class ControlContainerBase: public ControlParent {
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ControlContainerBase::GET_TYPE();

    private:
        bool previousReceiver = false;

    protected:
        Control* child = nullptr;

        virtual void setChild(Control* child) {
            if (this->child == child)
                return;
            if (this->child)
                this->child->Parent = nullptr;
            setPointer(this->child, child);
            if (this->child)
                this->child->Parent = this;
        }

    public:
        ~ControlContainerBase() {
            if (child) {
                child->Parent = nullptr;
                child->release();
            }
        }

        virtual bool focusNext() override;

        virtual bool focusPrevious() override;

        virtual bool focusUp() override;

        virtual bool focusDown() override;

        virtual bool focusLeft() override;

        virtual bool focusRight() override;

        virtual void dispatchStateChanged() override;

        virtual void dispatchThemeChanged() override;

        virtual void dispatchContextChanged() override;

        virtual void onMeasure() override;

        virtual void onLayout(float x, float y, float width, float height) override {
            if (child)
                child->layout(0, 0, width, height);
        }

        virtual void onUpdate(const uint64_t time) override {
            if (child)
                child->onUpdate(time);
        }

        virtual void onDraw(ICanvas& canvas) override {
            if (child)
                child->draw(canvas);
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual void resolveConstraints(ConstraintGraph& graph) override;

#ifdef _DEBUG
        virtual void validate() const override;

        virtual String printTree() const;
#endif
    };
}