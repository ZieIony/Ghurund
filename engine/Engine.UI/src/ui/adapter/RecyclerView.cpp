#include "ghuipch.h"
#include "RecyclerView.h"
#include "core/reflection/TypeBuilder.h"

#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& RecyclerView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<RecyclerView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<RecyclerView>(NAMESPACE_NAME, GH_STRINGIFY(RecyclerView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void RecyclerView::onDraw(ICanvas& canvas) {
        if (!layoutManager)
            return;

        canvas.save();
        canvas.clipRect(0, 0, Size.width, Size.height);
        auto& scroll = layoutManager->Scroll;
        canvas.translate(scroll.x, scroll.y);
        for (Control* c : Children)
            c->draw(canvas);
        canvas.restoreClipRect();
        canvas.restore();
    }

    bool RecyclerView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (!layoutManager)
            return false;

        const FloatPoint& scroll = layoutManager->Scroll;
        return __super::dispatchMouseButtonEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
    }
    
    bool RecyclerView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (!layoutManager)
            return false;

        const FloatPoint& scroll = layoutManager->Scroll;
        return __super::dispatchMouseMotionEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
    }
    
    bool RecyclerView::dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
        if (layoutManager && childrenProvider) {
            if (args.Wheel == MouseWheel::VERTICAL) {
                layoutManager->scrollBy(0, (float)args.Delta);
                onScrolled();
                repaint();
            } else {
                layoutManager->scrollBy((float)args.Delta, 0);
                onScrolled();
                repaint();
            }
        }

        return OnMouseWheel(args);
    }
}
