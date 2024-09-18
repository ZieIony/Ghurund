#pragma once

#include "core/application/Layer.h"
#include "ui/RootView.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/UIContext.h"
#include "ui/constraint/WindowConstraint.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    template<class T>
    class UILayer:public Layer<T> {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<UILayer>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(UILayer))
                .withTemplateParam(getType<T>())
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

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
            rootView->Focused = Layer<T>::Focused;
            return true;
        }

    public:
        ~UILayer() {
            rootView->release();
        }

        void init(IUIContext& context) {
            this->context = &context;
            rootView = ghnew Ghurund::UI::RootView(*this->context);
            rootViewWidth.set(ghnew WindowWidthConstraint(this->context->Window));
            rootViewHeight.set(ghnew WindowHeightConstraint(this->context->Window));
        }

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

        virtual void update(const uint64_t time) override {
            rootView->onUpdate(time);
            graph.clear();
            graph.add(rootViewWidth.get());
            graph.add(rootViewHeight.get());
            rootView->resolveConstraints(graph, *rootViewWidth.get(), *rootViewHeight.get());
            graph.sort();
            graph.evaluate();
            rootView->layout(0, 0, rootViewWidth->Value, rootViewHeight->Value);
        }

        void draw(ICanvas& canvas) {
            try {
                canvas.beginPaint();
                rootView->draw(canvas);
                canvas.endPaint();
            } catch (...) {}
        }
    };
}