#include "ghuipch.h"
#include "ControlContainer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/control/InvalidControl.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlContainer::GET_TYPE() {

        static auto PROPERTY_CHILD = Property<ControlContainer, Control*>("Child", (Control * (ControlContainer::*)()) & getChild, (void(ControlContainer::*)(Control*)) & setChild);

        static const auto CONSTRUCTOR = Constructor<ControlContainer>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<ControlContainer>(Ghurund::UI::NAMESPACE_NAME, "ControlContainer")
            .withProperty(PROPERTY_CHILD)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool ControlContainer::focusNext() {
        if (__super::focusNext())
            return true;
        return child && child->focusNext();
    }

    bool ControlContainer::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        return child && child->focusPrevious();
    }

    bool ControlContainer::focusUp() {
        if (__super::focusUp())
            return true;
        return child && child->focusUp();
    }

    bool ControlContainer::focusDown() {
        if (__super::focusDown())
            return true;
        return child && child->focusDown();
    }

    bool ControlContainer::focusLeft() {
        if (__super::focusLeft())
            return true;
        return child && child->focusLeft();
    }

    bool ControlContainer::focusRight() {
        if (__super::focusRight())
            return true;
        return child && child->focusRight();
    }

    void ControlContainer::dispatchStateChanged() {
        __super::dispatchStateChanged();
        if (child)
            child->dispatchStateChanged();
    }

    void ControlContainer::dispatchThemeChanged() {
        __super::dispatchThemeChanged();
        if (child)
            child->dispatchThemeChanged();
    }

    void ControlContainer::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (child)
            child->dispatchContextChanged();
    }

    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        measuredSize.width = std::max(minSize.width, preferredSize.width.Value);
        measuredSize.height = std::max(minSize.height, preferredSize.height.Value);

        if (child) {
            child->measure(
                preferredSize.width.Type == PreferredSize::Type::PIXELS ? preferredSize.width.Value : parentWidth,
                preferredSize.height.Type == PreferredSize::Type::PIXELS ? preferredSize.height.Value : parentHeight
            );
            float childWidth = child->PreferredSize.width.Type == PreferredSize::Type::PIXELS ? child->PreferredSize.width.Value : child->MeasuredSize.width;
            measuredSize.width = std::max(measuredSize.width, childWidth);
            float childHeight = child->PreferredSize.height.Type == PreferredSize::Type::PIXELS ? child->PreferredSize.height.Value : child->MeasuredSize.height;
            measuredSize.height = std::max(measuredSize.height, childHeight);
        }
    }

    bool ControlContainer::dispatchKeyEvent(const KeyEventArgs& event) {
        if (child && child->dispatchKeyEvent(event))
            return true;
        return __super::dispatchKeyEvent(event);
    }

    bool ControlContainer::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (child
            && (capturedChild || child->canReceiveEvent(event))
            && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
            return true;
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (child) {
            if (capturedChild || child->canReceiveEvent(event)) {
                previousReceiver = true;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, true)))
                    return true;
            } else if (previousReceiver) {
                previousReceiver = false;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, false)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlContainer::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (child && child->canReceiveEvent(event) && child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
            return true;
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlContainer::find(const AString& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }

    Control* ControlContainer::find(const Ghurund::Core::Type& type) {
        if (Type == type)
            return this;
        if (child)
            return child->find(type);
        return nullptr;
    }

    void ControlContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto child = xml.FirstChildElement();
        if (child) {
            Control* control = loader.loadControl(*child);
            if (control) {
                Child = control;
            } else {
                Child = ghnew InvalidControl();
            }
            Child->release();
        }
    }
}