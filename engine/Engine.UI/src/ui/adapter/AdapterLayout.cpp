#include "ghuipch.h"
#include "AdapterLayout.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/Canvas.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& AdapterLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<AdapterLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<AdapterLayout>(NAMESPACE_NAME, GH_STRINGIFY(AdapterLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    inline bool AdapterLayout::onMouseWheelEvent(const MouseWheelEventArgs& args) {
        if (args.Wheel == MouseWheel::VERTICAL) {
            return layoutManager->onScroll(0, (float)args.Delta/10);
        } else {
            return layoutManager->onScroll((float)args.Delta/10, 0);
        }
    }

    void AdapterLayout::onDraw(ICanvas& canvas) {
        if (!layoutManager)
            return;

        canvas.save();
        canvas.clipRect(0, 0, Size.Width, Size.Height);
        auto& scroll = layoutManager->Scroll;
        canvas.translate(scroll.x, scroll.y);
        __super::onDraw(canvas);
        canvas.restoreClipRect();
        canvas.restore();
    }
    
    void AdapterLayout::addChild(size_t adapterPosition, size_t groupPosition) {
        size_t type = itemAdapter->getType(adapterPosition);
        Control* control = [&]() {
            if (pool.isEmpty(type)) {
                return itemAdapter->makeControl(adapterPosition);
            } else {
                return pool.getControl(type);
            }
        }();
        itemAdapter->bind(*control, adapterPosition);
        SizeConstraints sizeConstraints = itemAdapter->makeSizeConstraints(adapterPosition);
        ConstraintSet constraints = makeConstraints({
            .width = sizeConstraints.width,
            .top = makeShared<ValueConstraint>(),
            .height = sizeConstraints.height
            });
        Children.insert(groupPosition, control, constraints);
        control->release();
        ConstraintGraph graph;
        sizeConstraints.width->resolve(*control, graph);
        sizeConstraints.height->resolve(*control, graph);
        graph.sort();
        graph.evaluate();
    }
    
    void AdapterLayout::removeChild(size_t adapterPosition, size_t groupPosition) {
        Control* child = Children[groupPosition].control.get();
        child->addReference();
        Children.removeAt(groupPosition);
        size_t type = itemAdapter->getType(adapterPosition);
        pool.recycle(child, type);
        child->release();
    }
/*
    bool AdapterLayout::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (!layoutManager)
            return false;

        //const FloatPoint& scroll = layoutManager->Scroll;
        return __super::dispatchMouseButtonEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
    }
    
    bool AdapterLayout::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (!layoutManager)
            return false;

        const FloatPoint& scroll = layoutManager->Scroll;
        return __super::dispatchMouseMotionEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
    }
    
    */
}
