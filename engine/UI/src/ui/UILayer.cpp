#include "ghuipch.h"
#include "UILayer.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& UILayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UILayer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UILayer::init(IUIContext& context) {
        if (rootView)
            return;
        this->context = &context;
        rootView = ghnew Ghurund::UI::RootView(*this->context);
        rootViewWidth.set(ghnew WindowWidthConstraint(this->context->Window));
        rootViewHeight.set(ghnew WindowHeightConstraint(this->context->Window));

        this->context->Window.sizeChanged += [&](const Window& window) {
            rootView->requestLayout();
            return true;
        };
    }
    
    void UILayer::uninit() {
        if (!rootView)
            return;
        rootView->release();
        rootView = nullptr;
    }
    
    void UILayer::update(const uint64_t time) {
        rootView->onUpdate(time);
        graph.clear();
        graph.add(rootViewWidth.get());
        graph.add(rootViewHeight.get());
        rootView->resolveConstraints(graph, *rootViewWidth.get(), *rootViewHeight.get());
        graph.sort();
        graph.evaluate();
        rootView->layout(0, 0, rootViewWidth->Value, rootViewHeight->Value);
    }
    
    void UILayer::draw(RenderGroup& group) {
        rootView->draw(group);
    }
}