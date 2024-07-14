#pragma once

#include "core/application/Layer.h"
#include "ui/RootView.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/UIContext.h"
#include "core/window/Window.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class UILayer:public Layer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = UILayer::GET_TYPE();
#pragma endregion

    protected:
        IUIContext* context;
        RootView* rootView;
        IntrusivePointer<Constraint> rootViewWidth, rootViewHeight;
        ConstraintGraph graph;

        virtual bool onSizeChanged() override {
            rootView->requestLayout();
            return true;
        }

        virtual bool onFocusedChanged() override {
            rootView->Focused = Focused;
            return true;
        }

    public:
        ~UILayer() {
            rootView->release();
        }

        void init(IUIContext& context);

        inline RootView& getRoot() {
            return *rootView;
        }

        __declspec(property(get = getRoot)) RootView& Root;

        inline IUIContext& getContext() {
            return *context;
        }

        __declspec(property(get = getContext)) IUIContext& Context;

        virtual bool dispatchKeyEvent(const KeyEventArgs& args) {
            return rootView->dispatchKeyEvent(args);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
            return rootView->dispatchMouseButtonEvent(args);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            return rootView->dispatchMouseMotionEvent(args);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            return rootView->dispatchMouseWheelEvent(args);
        }

        virtual void update(const uint64_t time) override;

        void draw(ICanvas& canvas);
    };
}