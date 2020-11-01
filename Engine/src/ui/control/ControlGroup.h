#pragma once

#include "ControlParent.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/ChildrenList.h"

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
    private:
        ChildrenList children;
        Control* capturedChild = nullptr;
        Control* previousReceiver = nullptr;

    protected:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            for (Control* c : Children) {
                if (!c->Visible)
                    continue;
                c->measure(
                    PreferredSize.width >= 0 ? PreferredSize.width : parentWidth,
                    PreferredSize.height >= 0 ? PreferredSize.height : parentHeight
                );
            }
        }

    public:
        ControlGroup():children(*this) {
            PreferredSize.width = PreferredSize::Width::FILL;
            PreferredSize.height = PreferredSize::Height::FILL;
        }

        ~ControlGroup() {
            if (capturedChild)
                capturedChild->release();
            if (previousReceiver)
                previousReceiver->release();
        }

        inline ChildrenList& getChildren() {
            return children;
        }

        inline const ChildrenList& getChildren() const {
            return children;
        }

        inline void setChildren(const std::initializer_list<Control*>& controls) {
            children.clear();
            children.addAll(controls);
        }

        __declspec(property(get = getChildren, put = setChildren)) ChildrenList& Children;

        virtual bool focusNext();

        virtual bool focusPrevious();

        virtual void update(const Timer& timer) override {
            for (Control* c : children)
                c->update(timer);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);

        static const Ghurund::Type& TYPE() {
            static Ghurund::Type TYPE = TypeBuilder<ControlGroup>(NAMESPACE_NAME, GH_STRINGIFY(ControlGroup))
                .withConstructor(NoArgsConstructor<ControlGroup>())
                .withSupertype(Control::TYPE());

            return TYPE;
        }

        virtual const Ghurund::Type& getType() const override {
            return ControlGroup::TYPE();
        }
    };

    typedef ScopedPointer<ControlGroup> ControlGroupPtr;
}