#pragma once

#include "ControlList.h"
#include "ControlParent.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ControlGroup::GET_TYPE();
#pragma endregion

    private:
        ControlList children;
        Control* previousReceiver = nullptr;

    protected:
        virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

        virtual void onMeasure() override;

        virtual void onLayout(float x, float y, float width, float height) override;

    public:
        ControlGroup():children(*this) {}

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

        virtual void onDraw(ICanvas& canvas) override;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        using Control::find;

        virtual Control* find(const Ghurund::Core::AString& name) override;

        virtual Control* find(const Ghurund::Core::Type& type) override;

        virtual void resolveConstraints(ConstraintGraph& graph) override;

#ifdef _DEBUG
        virtual void validate() const override;

        virtual String printTree() const;
#endif
    };
}