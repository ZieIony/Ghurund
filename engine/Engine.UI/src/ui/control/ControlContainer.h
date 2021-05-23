#pragma once

#include "ControlParent.h"

#include "reflection_6cd843c9_baef_42ed_8438_114be2efc99b.h"

namespace Ghurund::UI {
    class ControlContainer: public ControlParent {
        reflection_6cd843c9_baef_42ed_8438_114be2efc99b

    private:
        Control* child = nullptr;
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

        inline const Control* getChild() const {
            return child;
        }

        inline void setChild(Control* child) {
            if (this->child == child)
                return;
            if (Focused)
                clearFocus();
            if (this->child)
                this->child->Parent = nullptr;
            setPointer(this->child, child);
            if (this->child)
                this->child->Parent = this;
        }

        __declspec(property(get = getChild, put = setChild)) Control* Child;

        virtual bool focusNext() override;

        virtual bool focusPrevious() override;

        virtual bool focusUp() override;

        virtual bool focusDown() override;

        virtual bool focusLeft() override;

        virtual bool focusRight() override;

        virtual void dispatchStateChanged() override;

        virtual void dispatchThemeChanged() override;

        virtual void dispatchContextChanged() override;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override {
            if (child)
                child->layout(0, 0, width, height);
        }

        virtual void onUpdate(const uint64_t time) override {
            if (child)
                child->onUpdate(time);
        }

        virtual void onDraw(Canvas& canvas) override {
            if (child)
                child->draw(canvas);
        }

        virtual bool dispatchKeyEvent(const Ghurund::KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const Ghurund::MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const Ghurund::MouseWheelEventArgs& event) override;

        virtual Control* find(const AString& name);

        virtual Control* find(const Ghurund::Type& type);

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

#ifdef _DEBUG
        virtual void validate() override {
            __super::validate();
            if(child)
                child->validate();
        }
#endif
    };
}