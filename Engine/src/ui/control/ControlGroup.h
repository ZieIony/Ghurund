#pragma once

#include "ChildrenList.h"
#include "ControlParent.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
    private:
        ChildrenList children;
        Control* previousReceiver = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<ControlGroup>();
            static Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ControlGroup))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

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

        virtual bool dispatchKeyEvent(const Ghurund::Input::KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const Ghurund::Input::MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const Ghurund::Input::MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);

        virtual Control* find(const Ghurund::Type& type);

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

#ifdef _DEBUG
        virtual String logTree();
#endif

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return GET_TYPE();
        }
    };
}