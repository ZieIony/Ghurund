#pragma once

#include "ControlParent.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/ChildrenList.h"

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
    private:
        ChildrenList children;
        Control* previousReceiver = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ControlGroup>();
        static const Ghurund::Type& GET_TYPE() {
            static Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ControlGroup))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

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

        virtual void dispatchContextChanged() override;

        virtual void onUpdate(const uint64_t time) override {
            for (Control* c : children)
                c->onUpdate(time);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);

        virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) override;

#ifdef _DEBUG
        virtual String logTree() {
            String log = __super::logTree();
            for (Control* child : children) {
                auto array = child->logTree().split(_T("\n"));
                if (!array.Empty) {
                    String& s = array[0];
                    log.add(fmt::format(_T(" + {}\n"), s).c_str());
                }
                for (size_t i = 1; i < array.Size; i++) {
                    String& s = array[i];
                    if (children[children.Size - 1] == child) {
                        log.add(fmt::format(_T("   {}\n"), s).c_str());
                    } else {
                        log.add(fmt::format(_T(" | {}\n"), s).c_str());
                    }
                }
            }
            return log;
        }
#endif

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return GET_TYPE();
        }
    };
}