#include "ghuipch.h"
#include "UILayer.h"

#include "ui/Canvas.h"
#include "ui/RootView.h"
#include <ui/constraint/WindowConstraint.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& UILayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UILayer>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(UILayer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UILayer::init(IUIContext& context) {
        this->context = &context;
        rootView = ghnew Ghurund::UI::RootView(*this->context);
        rootViewWidth.set(ghnew WindowWidthConstraint(this->context->Window));
        rootViewHeight.set(ghnew WindowHeightConstraint(this->context->Window));
    }
    
    void UI::UILayer::update(const uint64_t time) {
        rootView->onUpdate(time);
        graph.clear();
        graph.add(rootViewWidth.get());
        graph.add(rootViewHeight.get());
        rootView->resolveConstraints(graph, *rootViewWidth.get(), *rootViewHeight.get());
        graph.sort();
        graph.evaluate();
        rootView->layout(0, 0, rootViewWidth->Value, rootViewHeight->Value);
    }

    void UILayer::draw(ICanvas& canvas) {
		try {
			canvas.beginPaint();
			rootView->draw(canvas);
			canvas.endPaint();
		} catch (...) {}
	}
}