#pragma once

#include "engine/application/Layer.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/WindowConstraint.h"
#include "ui/RootView.h"
#include "ui/UIContext.h"
#include <engine/graphics/RenderGroup.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;

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
        UIContext* context;
        RootView* rootView;
        IntrusivePointer<Constraint> rootViewWidth, rootViewHeight;
        ConstraintGraph graph;

        virtual bool onSizeChanged() override {
            rootView->requestLayout();
            return true;
        }

        virtual bool onFocusedChanged() override {
            rootView->Focused = Layer::Focused;
            return true;
        }

    public:
        ~UILayer() {
            uninit();
        }

        void init(UIContext& context);

        void uninit();

        inline RootView& getRoot() {
            return *rootView;
        }

        __declspec(property(get = getRoot)) RootView& Root;

        inline const Ghurund::UI::Theme* getTheme() const {
            return rootView->Theme;
        }

        inline void setTheme(Ghurund::UI::Theme* theme) {
            rootView->Theme = theme;
        }

        __declspec(property(get = getTheme, put = setTheme)) const Ghurund::UI::Theme* Theme;

        inline Ghurund::UI::Control* getContent() {
            return rootView->Child;
        }

        inline void setContent(Ghurund::UI::Control* content) {
            rootView->Child = content;
        }

        __declspec(property(get = getContent, put = setContent)) Ghurund::UI::Control* Content;

        inline UIContext& getContext() {
            return *context;
        }

        __declspec(property(get = getContext)) UIContext& Context;

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

        virtual void draw(RenderingContext& renderingContext, ParameterManager& parameterManager) override;
    };
}