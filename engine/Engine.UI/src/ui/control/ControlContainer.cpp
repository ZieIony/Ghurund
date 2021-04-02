#include "ghuipch.h"
#include "ControlContainer.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Type& ControlContainer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ControlContainer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ControlContainer))
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
        if (child) {
            child->measure(
                preferredSize.width >= 0 ? (float)preferredSize.width : parentWidth,
                preferredSize.height >= 0 ? (float)preferredSize.height : parentHeight
            );
        }

        measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
        if (child) {
            float childWidth = (float)child->PreferredSize.width >= 0 ? (float)child->PreferredSize.width : child->MeasuredSize.width;
            measuredSize.width = std::max(measuredSize.width, childWidth);
            float childHeight = (float)child->PreferredSize.height >= 0 ? (float)child->PreferredSize.height : child->MeasuredSize.height;
            measuredSize.height = std::max(measuredSize.height, childHeight);
        }
    }

    bool ControlContainer::dispatchKeyEvent(const Ghurund::KeyEventArgs& event) {
        if (child && child->dispatchKeyEvent(event))
            return true;
        return __super::dispatchKeyEvent(event);
    }

    bool ControlContainer::dispatchMouseButtonEvent(const Ghurund::MouseButtonEventArgs& event) {
        if (child
            && (capturedChild || child->canReceiveEvent(event))
            && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
            return true;
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& event) {
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

    bool ControlContainer::dispatchMouseWheelEvent(const Ghurund::MouseWheelEventArgs& event) {
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

    Control* ControlContainer::find(const Ghurund::Type& type) {
        if (Type == type)
            return this;
        if (child)
            return child->find(type);
        return nullptr;
    }

    Status ControlContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto child = xml.FirstChildElement();
        if (child) {
            Control* control = loader.loadControl(*child);
            if (control) {
                Child = control;
                control->release();
            }
        }
        return Status::OK;
    }
}