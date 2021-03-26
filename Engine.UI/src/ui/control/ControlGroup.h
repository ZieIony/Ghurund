#pragma once

#include "ControlList.h"
#include "ControlParent.h"

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
    private:
        ControlList children;
        Control* previousReceiver = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

    protected:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            for (Control* c : Children) {
                if (!c->Visible)
                    continue;
                c->measure(
                    PreferredSize.width >= 0 ? (float)PreferredSize.width : parentWidth,
                    PreferredSize.height >= 0 ? (float)PreferredSize.height : parentHeight
                );
            }
        }

    public:
        ControlGroup():children(*this) {
            PreferredSize.width = PreferredSize::Width::FILL;
            PreferredSize.height = PreferredSize::Height::FILL;
        }

        ~ControlGroup() {
            if (previousReceiver)
                previousReceiver->release();
        }

        inline ControlList& getChildren() {
            return children;
        }

        inline const ControlList& getChildren() const {
            return children;
        }

        inline void setChildren(const std::initializer_list<Control*>& controls) {
            children.clear();
            children.addAll(controls);
        }

        __declspec(property(get = getChildren, put = setChildren)) ControlList& Children;

        virtual bool focusNext() override;

        virtual bool focusPrevious() override;

        virtual bool focusUp() override;

        virtual bool focusDown() override;

        virtual bool focusLeft() override;

        virtual bool focusRight() override;

        virtual void dispatchStateChanged() override;

        virtual void dispatchThemeChanged() override;

        virtual void dispatchContextChanged() override;

        virtual void onUpdate(const uint64_t time) override {
            for (Control* c : children)
                c->onUpdate(time);
        }

        virtual void onDraw(Canvas& canvas) override;

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
            for (Control* child : children)
                child->validate();
        }
#endif

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return GET_TYPE();
        }
    };
}